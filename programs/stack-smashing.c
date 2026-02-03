/* Copying into array too small for the source string */
#include <stdio.h>
#include <string.h>
int main()
{
    char dest[3];
    strcpy(dest, "Hello");
    printf("%s\n", dest);
    return 0;
}
/* main.c: In function ‘main’:
main.c:7:5: warning: ‘__builtin_memcpy’ writing 6 bytes into a region of size 3 overflows the destination [-Wstringop-overflow=]
    7 |     strcpy(dest, "Hello");
      |     ^~~~~~~~~~~~~~~~~~~~~
main.c:6:10: note: destination object ‘dest’ of size 3
    6 |     char dest[3];
      |          ^~~~
Hello
*** stack smashing detected ***: terminated
*/