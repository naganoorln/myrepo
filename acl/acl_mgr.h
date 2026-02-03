#ifndef ACL_MGR_H
#define ACL_MGR_H

#include "acl_types.h"

int acl_mgr_init(int unit);
int acl_mgr_add_rule(acl_rule_t *rule);

#endif

