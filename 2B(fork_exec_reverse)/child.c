#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("\nChild (PID %d) – Received array from parent:\n", getpid());

    int i;
    for(i = 1; i < argc; i++)
        printf("%s ", argv[i]);

    printf("\n\nChild – Array in reverse order:\n");
    for(i = argc - 1; i > 0; i--)
        printf("%s ", argv[i]);

    printf("\n");
    return 0;
}

