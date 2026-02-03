//#include <cpssDxCh.h>
//#include <string.h>
#include "acl_types.h"

int marvell_acl_init(int dev)
{
    /*cpssDxChPclIngressPolicyEnable(
        dev,
        CPSS_PCL_DIRECTION_INGRESS,
        CPSS_PCL_LOOKUP_0_E,
        GT_TRUE);*/
    return 0;
}

int marvell_acl_add(int dev, acl_rule_t *rule)
{
    /*CPSS_DXCH_PCL_RULE_FORMAT_UNT pclRule;
    CPSS_DXCH_PCL_ACTION_STC action;

    memset(&pclRule, 0, sizeof(pclRule));
    memset(&action, 0, sizeof(action));

    pclRule.ruleIngrStdNotIp.srcIp.arIP[0] =
        rule->src_ip;
    pclRule.ruleIngrStdNotIp.srcIpMask.arIP[0] =
        rule->src_mask;

    action.pktCmd =
        (rule->action == ACL_ACTION_DROP) ?
        CPSS_PACKET_CMD_DROP_HARD_E :
        CPSS_PACKET_CMD_FORWARD_E;

    cpssDxChPclRuleSet(dev,
                       CPSS_PCL_RULE_SIZE_STD_E,
                       0,
                       &pclRule,
                       &action);*/
    return 0;
}

