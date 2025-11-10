#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int n, i, a[20];
    printf("Enter number of integers: ");
    scanf("%d", &n);
    printf("Enter %d integers:\n", n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    pid_t pid = fork();

    if(pid < 0)
        printf("Fork failed\n");

    else if(pid == 0)
    {
        // ----- Child -----
        printf("\nChild process executing new program using execve...\n");

        char *args[] = {"./child", NULL};
        execve(args[0], args, NULL);

        // if execve fails
        perror("execve failed");
        exit(1);
    }

    else
    {
        // ----- Parent -----
        int t;
        for(i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                if(a[i] > a[j])
                { t=a[i]; a[i]=a[j]; a[j]=t; }

        printf("\nParent (PID %d) – Ascending order:\n", getpid());
        for(i=0;i<n;i++)
            printf("%d ", a[i]);
        printf("\n");

        wait(NULL);   // parent waits – avoids zombie
        printf("Parent: child finished execution.\n");
    }
    return 0;
}

