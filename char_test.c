#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    char name[] = "siva";
    printf("name = %p\n", name);
    printf("&name[0] = %p\n", &name[0]);
    printf("&name[1] = %p\n", &name[1]);
    printf("&name[2] = %p\n", &name[2]);
    printf("&name[3] = %p\n", &name[3]);

    printf("name printed as %%s is %s\n", name);


    printf("*name = %c\n", *name);
    printf("name[0] = %c\n", name[0]);

    printf("sizeof(name) is %d\n", sizeof(name));
    for (i = 0; i < sizeof(name) - 1; i++)
    {
        printf("%c\n", *(name + i));
    }
    printf("shit\n");

    printf("%s\n", name);
    printf("%c\n", *name);

    return 0;
}
