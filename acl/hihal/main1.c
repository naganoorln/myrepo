#include <stdio.h>
//#include <bcm/init.h>
#include "acl_mgr.h"

void cli_process(char *line);

int main(void)
{
    int unit = 0;
    char line[128];

    printf("Booting system...\n");

    //bcm_init(unit);
    acl_mgr_init(unit);

    printf("System ready\n");
    printf("Type: acl add src-ip 10.1.1.1 drop\n");

    while (1) {
        printf("nbn# ");
        if (!fgets(line, sizeof(line), stdin))
            break;
        cli_process(line);
    }

    return 0;
}

