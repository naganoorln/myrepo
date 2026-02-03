//#include <bcm/field.h>
//#include <bcm/error.h>
#include "acl_types.h"

//static bcm_field_group_t group;

int bcm_acl_init(int unit)
{
    /*bcm_field_qset_t qset;
    bcm_field_aset_t aset;

    bcm_field_qset_init(&qset);
    bcm_field_qset_add(&qset, bcmFieldQualifySrcIp);

    bcm_field_aset_init(&aset);
    bcm_field_aset_add(&aset, bcmFieldActionDrop);

    bcm_field_group_create(unit, qset,
                           BCM_FIELD_GROUP_PRIO_ANY,
                           &group);

    bcm_field_group_action_set(unit, group, aset);*/
    return 0;
}

int bcm_acl_add(int unit, acl_rule_t *rule)
{
    /*bcm_field_entry_t entry;

    bcm_field_entry_create(unit, group, &entry);
    bcm_field_qualify_SrcIp(unit, entry,
                            rule->src_ip,
                            rule->src_mask);

    if (rule->action == ACL_ACTION_DROP)
        bcm_field_action_add(unit, entry,
                             bcmFieldActionDrop, 0, 0);

    bcm_field_entry_install(unit, entry);*/
    return 0;
}

