#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int n, i, a[20], j, t;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // sort ascending
    for(i = 0; i < n-1; i++)
        for(j = i+1; j < n; j++)
            if(a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }

    printf("\nParent (PID %d) – Sorted array:\n", getpid());
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0) {
        // --- Child process ---
        char *args[25];
        char arr_str[10];
        args[0] = "./child";

        for(i = 0; i < n; i++) {
            sprintf(arr_str, "%d", a[i]);
            args[i + 1] = strdup(arr_str);
        }
        args[n + 1] = NULL;

        printf("\nChild executing execve with sorted array...\n");
        execve(args[0], args, NULL);

        perror("execve failed");
        exit(1);
    }
    else {
        wait(NULL);
        printf("Parent: child finished execution.\n");
    }
    return 0;
}

