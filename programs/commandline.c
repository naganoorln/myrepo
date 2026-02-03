#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
static int sensor_value = 0;
bool sensor_set(int value)
{
    sensor_value = value;
    return true;
}
int sensor_get()
{
    return sensor_value;
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s set <value> | get\n", argv[0]);
    }
    if(strcmp(argv[1],"set") ==0)
    {
        if(argc != 3)
        {
            printf("Usage: %s set <value>\n", argv[0]);
            return 1;
        }
        int value = atoi(argv[2]);
        if(sensor_set(value))
        {
            printf(" sensor value set to %d. \n",value);
        } else {
            printf("Failed to set sensor value.\n");
        }
    } else if(strcmp(argv[1], "get") == 0) {
        int value = sensor_get();
        printf("Current sensor value: %d\n",value);
    } else {
        printf("Invalid command. Use 'set or 'get.\n");
        return 1;
    }
    return 0;
}
    
        
        

        

