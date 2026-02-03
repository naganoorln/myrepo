#ifndef ACL_HAL_H
#define ACL_HAL_H

#include "acl_types.h"

int acl_hal_init(int unit);
int acl_hal_add_rule(int unit, acl_rule_t *rule);

#endif

