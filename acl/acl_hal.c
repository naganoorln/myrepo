//#include <bcm/field.h>
//#include <bcm/error.h>
#include "acl_hal.h"

//static bcm_field_group_t acl_group = -1;

int acl_hal_init(int unit)
{
    /*bcm_field_qset_t qset;
    bcm_field_aset_t aset;

    bcm_field_qset_init(&qset);
    bcm_field_qset_add(&qset, bcmFieldQualifySrcIp);

    bcm_field_aset_init(&aset);
    bcm_field_aset_add(&aset, bcmFieldActionDrop);
    bcm_field_aset_add(&aset, bcmFieldActionForward);

    BCM_IF_ERROR_RETURN(
        bcm_field_group_create(unit, qset,
                               BCM_FIELD_GROUP_PRIO_ANY,
                               &acl_group)
    );

    BCM_IF_ERROR_RETURN(
        bcm_field_group_action_set(unit, acl_group, aset)
    );*/

    return 0 ; //BCM_E_NONE;
}

int acl_hal_add_rule(int unit, acl_rule_t *rule)
{
    /*bcm_field_entry_t entry;

    BCM_IF_ERROR_RETURN(
        bcm_field_entry_create(unit, acl_group, &entry)
    );

    BCM_IF_ERROR_RETURN(
        bcm_field_qualify_SrcIp(unit, entry,
                                rule->src_ip,
                                rule->src_mask)
    );

    if (rule->action == ACL_ACTION_DROP) {
        BCM_IF_ERROR_RETURN(
            bcm_field_action_add(unit, entry,
                                 bcmFieldActionDrop, 0, 0)
        );
    }

    BCM_IF_ERROR_RETURN(
        bcm_field_entry_install(unit, entry)
    );*/

    return 0; // BCM_E_NONE;
}

