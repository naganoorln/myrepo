#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void display(char *input) {
    char buffer[16];
    
    //strncpy(buffer, input, (sizeof(buffer) - 1));
    //buffer[sizeof(buffer -1)] = '\0';
    strcpy(buffer, input); // stack over flow error

    puts(buffer);

}

int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        printf("Usage: %s <Input string>\n", argv[0]);
        return 1;
    }
    display(argv[1]);

    return 0;
}
