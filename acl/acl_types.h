#ifndef ACL_TYPES_H
#define ACL_TYPES_H

#include <stdint.h>

typedef enum {
    ACL_ACTION_PERMIT = 0,
    ACL_ACTION_DROP   = 1
} acl_action_t;

typedef struct {
    uint32_t src_ip;
    uint32_t src_mask;
    acl_action_t action;
} acl_rule_t;

#endif

