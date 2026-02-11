#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NF_ACCEPT 1
#define NF_DROP   0

#define PF_INET 2

#define NF_INET_PRE_ROUTING  0
#define NF_INET_LOCAL_IN     1
#define NF_INET_FORWARD      2
#define NF_INET_LOCAL_OUT    3
#define NF_INET_POST_ROUTING 4

#define MAX_HOOKS 10
#define MAX_HOOKNUM 5

/* Fake sk_buff */
struct sk_buff {
    int protocol;   /* 1=ICMP, 6=TCP, 17=UDP */
    char src_ip[16];
    char dst_ip[16];
};

/* Fake nf_hook_state */
struct nf_hook_state {
    int hook;
    int pf;
};

/* Hook function type */
typedef unsigned int (*nf_hookfn)(
    void *priv,
    struct sk_buff *skb,
    const struct nf_hook_state *state
);

/* Hook structure (like kernel) */
struct nf_hook_ops {
    nf_hookfn hook;
    int pf;
    int hooknum;
    int priority;
    void *priv;
};

/* Hook storage per hooknum */
struct nf_hook_ops *hook_table[MAX_HOOKNUM][MAX_HOOKS];
int hook_count[MAX_HOOKNUM] = {0};

/* Register Hook */
void nf_register_net_hook(struct nf_hook_ops *ops)
{
    int h = ops->hooknum;
    int count = hook_count[h];

    hook_table[h][count] = ops;
    hook_count[h]++;

    /* Sort by priority (lower first) */
    for (int i = 0; i < hook_count[h] - 1; i++) {
        for (int j = i + 1; j < hook_count[h]; j++) {
            if (hook_table[h][i]->priority >
                hook_table[h][j]->priority) {

                struct nf_hook_ops *tmp = hook_table[h][i];
                hook_table[h][i] = hook_table[h][j];
                hook_table[h][j] = tmp;
            }
        }
    }
}

/* Simulate nf_hook() */
unsigned int nf_hook(int pf, int hooknum, struct sk_buff *skb)
{
    struct nf_hook_state state;
    state.hook = hooknum;
    state.pf = pf;

    for (int i = 0; i < hook_count[hooknum]; i++) {
        struct nf_hook_ops *ops = hook_table[hooknum][i];

        if (ops->pf != pf)
            continue;

        unsigned int verdict =
            ops->hook(ops->priv, skb, &state);

        if (verdict == NF_DROP) {
            printf("Packet dropped at hook %d (priority %d)\n",
                   hooknum, ops->priority);
            return NF_DROP;
        }
    }

    return NF_ACCEPT;
}

/* Example Firewall Hook */
unsigned int my_firewall(void *priv,
                         struct sk_buff *skb,
                         const struct nf_hook_state *state)
{
    if (skb->protocol == 1) {
        printf("Firewall: Dropping ICMP packet\n");
        return NF_DROP;
    }

    return NF_ACCEPT;
}

/* Logger Hook */
unsigned int logger(void *priv,
                    struct sk_buff *skb,
                    const struct nf_hook_state *state)
{
    printf("Logger: Packet at hook %d from %s to %s\n",
           state->hook,
           skb->src_ip,
           skb->dst_ip);

    return NF_ACCEPT;
}

int main()
{
    struct nf_hook_ops fw_ops = {
        .hook = my_firewall,
        .pf = PF_INET,
        .hooknum = NF_INET_PRE_ROUTING,
        .priority = 5,
        .priv = NULL
    };

    struct nf_hook_ops log_ops = {
        .hook = logger,
        .pf = PF_INET,
        .hooknum = NF_INET_PRE_ROUTING,
        .priority = 10,
        .priv = NULL
    };

    nf_register_net_hook(&fw_ops);
    nf_register_net_hook(&log_ops);

    struct sk_buff packet;
    packet.protocol = 1; /* ICMP */
    strcpy(packet.src_ip, "192.168.1.10");
    strcpy(packet.dst_ip, "8.8.8.8");

    printf("Packet entering PRE_ROUTING\n");

    if (nf_hook(PF_INET, NF_INET_PRE_ROUTING, &packet)
        == NF_ACCEPT)
        printf("Packet accepted\n");
    else
        printf("Packet dropped\n");

    return 0;
}

