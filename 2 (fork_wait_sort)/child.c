#include <stdio.h>
#include <unistd.h>

int main()
{
    int n,i,a[20];
    printf("\nChild program started (PID %d)\n", getpid());
    printf("Enter number of integers: ");
    scanf("%d",&n);
    printf("Enter %d integers:\n", n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    int t;
    for(i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i] < a[j])
            { t=a[i]; a[i]=a[j]; a[j]=t; }

    printf("\nChild – Descending order:\n");
    for(i=0;i<n;i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

