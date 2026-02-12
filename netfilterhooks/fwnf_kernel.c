#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

#include "fwnf_rule.h"

#define DEV_NAME "myfw"

struct fw_rule_node {
    struct fw_rule rule;
    struct list_head list;
};

static LIST_HEAD(rule_list);
static int major;

static unsigned int fw_hook(void *priv,
                            struct sk_buff *skb,
                            const struct nf_hook_state *state)
{
    struct iphdr *ip;
    struct tcphdr *tcp;
    struct fw_rule_node *node;

    if (!skb)
        return NF_ACCEPT;

    ip = ip_hdr(skb);
    if (!ip || ip->protocol != IPPROTO_TCP)
        return NF_ACCEPT;

    tcp = tcp_hdr(skb);

    list_for_each_entry(node, &rule_list, list) {
        if (node->rule.dst_port == ntohs(tcp->dest))
            return node->rule.action ? NF_ACCEPT : NF_DROP;
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops nfho = {
    .hook     = fw_hook,
    .pf       = PF_INET,
    .hooknum  = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST,
};

static long fw_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    struct fw_rule rule;
    struct fw_rule_node *node, *tmp;
    struct fw_rule_list list;
    int index, i;

    switch (cmd) {

    case FW_IOCTL_ADD_RULE:
        if (copy_from_user(&rule, (void __user *)arg, sizeof(rule)))
            return -EFAULT;

        node = kmalloc(sizeof(*node), GFP_KERNEL);
        if (!node)
            return -ENOMEM;

        node->rule = rule;
        list_add_tail(&node->list, &rule_list);
        break;

    case FW_IOCTL_CLEAR_RULE:
        list_for_each_entry_safe(node, tmp, &rule_list, list) {
            list_del(&node->list);
            kfree(node);
        }
        break;

    case FW_IOCTL_LIST_RULES:
        list.count = 0;
        list_for_each_entry(node, &rule_list, list) {
            if (list.count >= FW_MAX_RULES)
                break;
            list.rules[list.count++] = node->rule;
        }
        if (copy_to_user((void __user *)arg, &list, sizeof(list)))
            return -EFAULT;
        break;

    case FW_IOCTL_DEL_RULE:
        if (copy_from_user(&index, (void __user *)arg, sizeof(int)))
            return -EFAULT;

        i = 0;
        list_for_each_entry_safe(node, tmp, &rule_list, list) {
            if (i++ == index) {
                list_del(&node->list);
                kfree(node);
                return 0;
            }
        }
        return -EINVAL;

    default:
        return -EINVAL;
    }
    return 0;
}

static const struct file_operations fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = fw_ioctl,
};

static int __init fw_init(void)
{
    major = register_chrdev(0, DEV_NAME, &fops);
    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Firewall loaded (major=%d)\n", major);
    return 0;
}

static void __exit fw_exit(void)
{
    struct fw_rule_node *node, *tmp;

    nf_unregister_net_hook(&init_net, &nfho);
    unregister_chrdev(major, DEV_NAME);

    list_for_each_entry_safe(node, tmp, &rule_list, list) {
        list_del(&node->list);
        kfree(node);
    }
    printk(KERN_INFO "Firewall unloaded\n");
}

module_init(fw_init);
module_exit(fw_exit);
MODULE_LICENSE("GPL");

