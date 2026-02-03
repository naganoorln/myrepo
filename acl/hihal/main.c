#include <stdio.h>
#include <string.h>
//#include <bcm/init.h>
#include "acl_mgr.h"

void cli_process(char *line);
void acl_hal_select_asic(int type);

#define ASIC_BCM     0
#define ASIC_MARVELL 1

void cli_clear_screen(void)
{
    /* ANSI escape sequence */
    printf("\033[2J\033[H");
    fflush(stdout);
}
int main(void)
{
    char line[128];
    int unit = 0;

    /* Select ASIC (could be EEPROM / DT / CLI) */
    /* acl_hal_select_asic(ASIC_BCM); */
     acl_hal_select_asic(ASIC_MARVELL);

    /*bcm_init(unit);*/        /* only meaningful for BCM */
    acl_mgr_init(unit);
    printf("Booting system...\n");
    printf("System ready\n");
    printf("Type: acl add src-ip 10.1.1.1 drop\n");
    while (1) {
        printf("nbn# ");
        fgets(line, sizeof(line), stdin);
	line[strcspn(line, "\n")] = 0;
	if (strcmp(line, "clear") == 0) 
	{
        	cli_clear_screen();
		continue;
	}	
        cli_process(line);
    }
}

