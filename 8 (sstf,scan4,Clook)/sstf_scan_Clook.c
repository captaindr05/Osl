#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SSTF(void);
int SCAN_Away(void);
int CLOOK_Away(void);

void sort(int a[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1]){ int t=a[j]; a[j]=a[j+1]; a[j+1]=t; }
}

int main(void){
    int ch, YN = 1;
    do{
        printf("\n********* MENU *********\n");
        printf("1. SSTF\n2. SCAN (away from spindle)\n3. C-LOOK (away from spindle)\n4. EXIT\n");
        printf("Enter choice: ");
        if (scanf("%d",&ch)!=1) return 0;

        switch(ch){
            case 1: SSTF(); break;
            case 2: SCAN_Away(); break;
            case 3: CLOOK_Away(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
        printf("\nContinue (1/0): ");
        if (scanf("%d",&YN)!=1) return 0;
    }while(YN==1);
    return 0;
}

/* ---------- SSTF ---------- */
int SSTF(void){
    int Rq[100], n, initial;
    int visited[100]={0};
    int TotalHeadMovement=0, done=0;

    printf("\nEnter no. of requests: ");
    scanf("%d",&n);
    printf("Enter the request sequence:\n");
    for(int i=0;i<n;i++) scanf("%d",&Rq[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);

    while(done<n){
        int minDist=1e9, idx=-1;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                int d = abs(Rq[i]-initial);
                if(d<minDist){ minDist=d; idx=i; }
            }
        }
        TotalHeadMovement += minDist;
        initial = Rq[idx];
        visited[idx]=1;
        done++;
    }
    printf("Total head movement (SSTF) = %d\n", TotalHeadMovement);
    return 0;
}

/* ---------- SCAN (away from spindle => toward higher tracks first) ---------- */
int SCAN_Away(void){
    int Rq[100], n, initial, size;
    int TotalHeadMovement=0;

    printf("\nEnter no. of requests: ");
    scanf("%d",&n);
    printf("Enter request sequence:\n");
    for(int i=0;i<n;i++) scanf("%d",&Rq[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);
    printf("Enter total disk size (last track index): ");
    scanf("%d",&size); /* e.g., if tracks are 0..199, enter 199 */

    sort(Rq,n);

    /* first index with request >= initial */
    int index = n;
    for(int i=0;i<n;i++){ if(Rq[i] >= initial){ index = i; break; } }

    /* move upward first */
    int head = initial;
    for(int i=index;i<n;i++){ TotalHeadMovement += abs(Rq[i]-head); head=Rq[i]; }

    /* go to end (size) then reverse */
    TotalHeadMovement += abs((size) - head); head = size;

    for(int i=index-1;i>=0;i--){ TotalHeadMovement += abs(Rq[i]-head); head=Rq[i]; }

    printf("Total head movement (SCAN away) = %d\n", TotalHeadMovement);
    return 0;
}

/* ---------- C-LOOK (away from spindle => serve higher first, wrap to lowest req) ---------- */
int CLOOK_Away(void){
    int Rq[100], n, initial;
    int TotalHeadMovement=0;

    printf("\nEnter no. of requests: ");
    scanf("%d",&n);
    printf("Enter request sequence:\n");
    for(int i=0;i<n;i++) scanf("%d",&Rq[i]);
    printf("Enter initial head position: ");
    scanf("%d",&initial);

    sort(Rq,n);

    int index = n;
    for(int i=0;i<n;i++){ if(Rq[i] >= initial){ index = i; break; } }

    int head = initial;

    /* go upward first */
    for(int i=index;i<n;i++){ TotalHeadMovement += abs(Rq[i]-head); head=Rq[i]; }

    /* wrap to lowest pending (no end cylinder visit) if any left */
    if(index>0){
        TotalHeadMovement += abs(head - Rq[0]);  /* wrap jump counted */
        head = Rq[0];
        for(int i=0;i<index;i++){ TotalHeadMovement += abs(Rq[i]-head); head=Rq[i]; }
    }

    printf("Total head movement (C-LOOK away) = %d\n", TotalHeadMovement);
    return 0;
}
