#ifndef FW_RULE_H
#define FW_RULE_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define FW_MAX_RULES 64

#define FW_IOCTL_ADD_RULE    _IOW('f', 1, struct fw_rule)
#define FW_IOCTL_CLEAR_RULE  _IO('f', 2)
#define FW_IOCTL_LIST_RULES  _IOR('f', 3, struct fw_rule_list)
#define FW_IOCTL_DEL_RULE    _IOW('f', 4, int)

struct fw_rule {
    __u32 src_ip;
    __u32 dst_ip;
    __u16 dst_port;
    __u8  action;   /* 0 = DROP, 1 = ACCEPT */
};

struct fw_rule_list {
    int count;
    struct fw_rule rules[FW_MAX_RULES];
};

#endif

