#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX 128
#define MAX_MATCHES 16

const char *commands[] = {
    "c",
    "clean",
    "clone",
    "install",
    "init",
    "remove",
    "help",
    NULL
};

struct termios orig;

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig);
    struct termios raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig);
}

/* Print choices on a new line */
/*void show_matches(char matches[][MAX], int count) {
    write(STDOUT_FILENO, "\n", 1);
    for (int i = 0; i < count; i++) {
        write(STDOUT_FILENO, matches[i], strlen(matches[i]));
        write(STDOUT_FILENO, "  ", 2);
    }
    write(STDOUT_FILENO, "\n> ", 3);
}*/
void show_matches(char matches[][MAX], int count,
                  const char *buf, int len) {
    write(STDOUT_FILENO, "\n", 1);

    for (int i = 0; i < count; i++) {
        write(STDOUT_FILENO, matches[i], strlen(matches[i]));
        write(STDOUT_FILENO, "  ", 2);
    }

    /* redraw prompt + buffer */
    write(STDOUT_FILENO, "\n> ", 3);
    write(STDOUT_FILENO, buf, len);
}


/* Find all matching commands */
int find_matches(const char *prefix, char matches[][MAX]) {
    int count = 0;
    size_t len = strlen(prefix);

    for (int i = 0; commands[i]; i++) {
        if (strncmp(commands[i], prefix, len) == 0) {
            strcpy(matches[count++], commands[i]);
            if (count == MAX_MATCHES)
                break;
        }
    }
    return count;
}

/* Replace buffer content with selected match */
void apply_match(char *buf, int *len, const char *match) {
    int back = *len;
    while (back--) write(STDOUT_FILENO, "\b \b", 3);

    strcpy(buf, match);
    *len = strlen(match);
    write(STDOUT_FILENO, buf, *len);
}

int main() {
    char buf[MAX] = {0};
    int len = 0;
    char c;

    char matches[MAX_MATCHES][MAX];
    int match_count = 0;
    int match_index = 0;
    int tab_count = 0;

    enable_raw_mode();
    write(STDOUT_FILENO, "> ", 2);

    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == '\n') break;

        if (c == '\t') {
            if (tab_count == 0) {
                match_count = find_matches(buf, matches);
                match_index = 0;

                if (match_count == 1) {
                    apply_match(buf, &len, matches[0]);
                } else if (match_count > 1) {
                    //show_matches(matches, match_count);
		    show_matches(matches, match_count, buf, len);
                }
            } else if (match_count > 1) {
                apply_match(buf, &len, matches[match_index]);
                match_index = (match_index + 1) % match_count;
            }
            tab_count++;
            continue;
        }

        /* Reset TAB state on normal input */
        tab_count = 0;
        match_count = 0;

        if (c == 127 && len > 0) {  /* Backspace */
            len--;
            write(STDOUT_FILENO, "\b \b", 3);
        } else {
            buf[len++] = c;
            write(STDOUT_FILENO, &c, 1);
        }
    }

    buf[len] = '\0';
    disable_raw_mode();

    printf("\nYou entered: %s\n", buf);
    return 0;
}

