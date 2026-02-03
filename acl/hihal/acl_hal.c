#include "acl_hal.h"

/* ASIC type */
typedef enum {
    ASIC_BCM,
    ASIC_MARVELL
} asic_type_t;

extern int bcm_acl_init(int);
extern int bcm_acl_add(int, acl_rule_t *);

extern int marvell_acl_init(int);
extern int marvell_acl_add(int, acl_rule_t *);

static struct {
    int (*init)(int);
    int (*add)(int, acl_rule_t *);
} hal_ops;

/* Called once at boot */
void acl_hal_select_asic(asic_type_t type)
{
    if (type == ASIC_BCM) {
        hal_ops.init = bcm_acl_init;
        hal_ops.add  = bcm_acl_add;
    } else {
        hal_ops.init = marvell_acl_init;
        hal_ops.add  = marvell_acl_add;
    }
}

int acl_hal_init(int unit)
{
    return hal_ops.init(unit);
}

int acl_hal_add_rule(int unit, acl_rule_t *rule)
{
    return hal_ops.add(unit, rule);
}

