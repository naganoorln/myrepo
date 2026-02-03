#include "acl_mgr.h"
#include "acl_hal.h"

static int g_unit;

int acl_mgr_init(int unit)
{
    g_unit = unit;
    return acl_hal_init(unit);
}

int acl_mgr_add_rule(acl_rule_t *rule)
{
    return acl_hal_add_rule(g_unit, rule);
}

