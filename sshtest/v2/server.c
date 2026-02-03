#include <libssh/libssh.h>
#include <libssh/server.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SSH_PORT 2222
#define THREAD_POOL_SIZE 10
#define QUEUE_SIZE 16

/* ===================== AUTH ===================== */

int check_credentials(const char *user, const char *pass) {
    return strcmp(user, "admin") == 0 &&
           strcmp(pass, "secret123") == 0;
}

int authenticate(ssh_session session) {
    ssh_message msg;

    while ((msg = ssh_message_get(session)) != NULL) {

        if (ssh_message_type(msg) == SSH_REQUEST_AUTH &&
            ssh_message_subtype(msg) == SSH_AUTH_METHOD_PASSWORD) {

            const char *user = ssh_message_auth_user(msg);
            const char *pass = ssh_message_auth_password(msg);

            printf("[AUTH] user=%s\n", user);

            if (check_credentials(user, pass)) {
                ssh_message_auth_reply_success(msg, 0);
                ssh_message_free(msg);
                return SSH_AUTH_SUCCESS;
            }
        }

        ssh_message_auth_set_methods(msg, SSH_AUTH_METHOD_PASSWORD);
        ssh_message_reply_default(msg);
        ssh_message_free(msg);
    }
    return SSH_AUTH_DENIED;
}

/* ================= INTERACTIVE SHELL ================= */

void interactive_shell(ssh_session session) {
    ssh_channel channel = NULL;
    ssh_message msg;

    /* Accept session channel */
    while ((msg = ssh_message_get(session)) != NULL) {
        if (ssh_message_type(msg) == SSH_REQUEST_CHANNEL_OPEN &&
            ssh_message_subtype(msg) == SSH_CHANNEL_SESSION) {

            channel = ssh_message_channel_request_open_reply_accept(msg);
            ssh_message_free(msg);
            break;
        }
        ssh_message_reply_default(msg);
        ssh_message_free(msg);
    }
    if (!channel) return;

    /* Accept PTY + shell */
    int shell_ok = 0;
    while (!shell_ok) {
        msg = ssh_message_get(session);
        if (!msg) break;

        if (ssh_message_type(msg) == SSH_REQUEST_CHANNEL &&
            ssh_message_subtype(msg) == SSH_CHANNEL_REQUEST_PTY) {
            ssh_message_channel_request_reply_success(msg);
        }
        else if (ssh_message_type(msg) == SSH_REQUEST_CHANNEL &&
                 ssh_message_subtype(msg) == SSH_CHANNEL_REQUEST_SHELL) {
            ssh_message_channel_request_reply_success(msg);
            shell_ok = 1;
        }
        else {
            ssh_message_reply_default(msg);
        }
        ssh_message_free(msg);
    }

    ssh_channel_write(channel,"Connected to SSH SERVER version 1.0\n", 37);
    ssh_channel_write(channel,"\rType 'help' to list available commands\n", 41);

    char line[256];
    int len = 0;
    char ch;

ssh_channel_write(channel, "\rssh> ", 6);

while (ssh_channel_read(channel, &ch, 1, 0) == 1) {

    /* Ignore LF */
    if (ch == '\n')
        continue;

    /* ENTER */
    if (ch == '\r') {
        ssh_channel_write(channel, "\r\n", 2);
        line[len] = '\0';

        /* PROCESS COMMAND */
        if (strcmp(line, "help") == 0) {
            ssh_channel_write(channel,
                "Commands:\r\n"
                " help\r\n"
                " whoami\r\n"
                " exit\r\n", 45);
        }
        else if (strcmp(line, "whoami") == 0) {
            ssh_channel_write(channel, "admin\r\n", 7);
        }
        else if (strcmp(line, "exit") == 0) {
            ssh_channel_write(channel, "Bye!\r\n", 6);
            break;
        }
        else if (len > 0) {
            ssh_channel_write(channel, "Unknown command\r\n", 17);
        }

        /* RESET */
        len = 0;
        ssh_channel_write(channel, "\rssh> ", 6);
        continue;
    }

    /* BACKSPACE */
    if (ch == 0x7f || ch == 0x08) {
        if (len > 0) {
            len--;
            ssh_channel_write(channel, "\b \b", 3);
        }
        continue;
    }

    /* NORMAL CHAR */
    if (len < sizeof(line) - 1) {
        line[len++] = ch;
        ssh_channel_write(channel, &ch, 1);  // SERVER ECHO
    }
}

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
}

/* ===================== THREAD POOL ===================== */

typedef struct {
    ssh_session sessions[QUEUE_SIZE];
    int head, tail, count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} session_queue_t;

session_queue_t queue;

/* Worker thread */
void *worker_thread(void *arg) {
    (void)arg;

    while (1) {
        pthread_mutex_lock(&queue.mutex);

        while (queue.count == 0)
            pthread_cond_wait(&queue.cond, &queue.mutex);

        ssh_session session = queue.sessions[queue.head];
        queue.head = (queue.head + 1) % QUEUE_SIZE;
        queue.count--;

        pthread_mutex_unlock(&queue.mutex);

        if (ssh_handle_key_exchange(session)) goto cleanup;
        if (authenticate(session) != SSH_AUTH_SUCCESS) goto cleanup;

        printf("[+] Client handled by worker %lu\n", pthread_self());
        interactive_shell(session);

cleanup:
        ssh_disconnect(session);
        ssh_free(session);
    }
    return NULL;
}

/* ===================== MAIN ===================== */

int main() {
    ssh_bind sshbind;
    int port = SSH_PORT;
    pthread_t workers[THREAD_POOL_SIZE];

    /* Init queue */
    memset(&queue, 0, sizeof(queue));
    pthread_mutex_init(&queue.mutex, NULL);
    pthread_cond_init(&queue.cond, NULL);

    /* Start workers */
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&workers[i], NULL, worker_thread, NULL);
        pthread_detach(workers[i]);
    }

    sshbind = ssh_bind_new();
    ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDPORT, &port);
    ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, "ssh_host_rsa_key");

    if (ssh_bind_listen(sshbind) < 0) {
        fprintf(stderr, "Listen failed\n");
        return 1;
    }

    printf("[+] SSH server listening on %d with %d workers\n",
           port, THREAD_POOL_SIZE);

    while (1) {
        ssh_session session = ssh_new();

        if (ssh_bind_accept(sshbind, session) < 0) {
            ssh_free(session);
            continue;
        }

        pthread_mutex_lock(&queue.mutex);

        if (queue.count == QUEUE_SIZE) {
            pthread_mutex_unlock(&queue.mutex);
            ssh_disconnect(session);
            ssh_free(session);
            printf("[!] Connection dropped (queue full)\n");
            continue;
        }

        queue.sessions[queue.tail] = session;
        queue.tail = (queue.tail + 1) % QUEUE_SIZE;
        queue.count++;

        pthread_cond_signal(&queue.cond);
        pthread_mutex_unlock(&queue.mutex);
    }

    ssh_bind_free(sshbind);
    return 0;
}

