

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid;
    int at;   // arrival time
    int bt;   // burst time (original)
    int rt;   // remaining time
    int ct;   // completion time
    int wt;   // waiting time
    int tat;  // turnaround time
} Proc;

/* read processes */
void read_procs(Proc *p, int n){
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("P%d Arrival Time: ", p[i].pid); scanf("%d",&p[i].at);
        printf("P%d Burst   Time: ", p[i].pid); scanf("%d",&p[i].bt);
        p[i].rt = p[i].bt; p[i].ct = p[i].wt = p[i].tat = 0;
    }
}

/* print table */
void print_table(Proc *p, int n){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

/* SJF Preemptive (Shortest Remaining Time First) */
void sjf_preemptive(Proc *p, int n){
    int completed = 0;
    int t = INT_MAX;
    for(int i=0;i<n;i++) if(p[i].at < t) t = p[i].at; // start at earliest arrival
    double tot_wt = 0, tot_tat = 0;

    while(completed < n){
        int idx = -1, minrt = INT_MAX;
        for(int i=0;i<n;i++){
            if(p[i].at <= t && p[i].rt > 0){
                if(p[i].rt < minrt){ minrt = p[i].rt; idx = i; }
                else if(p[i].rt == minrt && p[i].at < p[idx].at) idx = i;
            }
        }
        if(idx == -1){ t++; continue; } // CPU idle
        p[idx].rt--; t++;
        if(p[idx].rt == 0){
            completed++;
            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;
            tot_tat += p[idx].tat;
            tot_wt  += p[idx].wt;
        }
    }

    printf("\n--- SJF Preemptive (SRTF) ---\n");
    print_table(p,n);
    printf("Avg TAT = %.2f, Avg WT = %.2f\n", tot_tat/n, tot_wt/n);
}

/* Round Robin with arrival times */
void round_robin(Proc *orig, int n, int tq){
    Proc *p = malloc(sizeof(Proc)*n);
    for(int i=0;i<n;i++) p[i] = orig[i];

    int completed = 0;
    int t = INT_MAX;
    for(int i=0;i<n;i++) if(p[i].at < t) t = p[i].at;
    double tot_wt = 0, tot_tat = 0;

    while(completed < n){
        int done = 0;
        for(int i=0;i<n;i++){
            if(p[i].at <= t && p[i].rt > 0){
                done = 1;
                int exec = (p[i].rt > tq) ? tq : p[i].rt;
                p[i].rt -= exec; t += exec;
                if(p[i].rt == 0){
                    completed++;
                    p[i].ct = t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt  = p[i].tat - p[i].bt;
                    tot_tat += p[i].tat;
                    tot_wt  += p[i].wt;
                }
            }
        }
        if(!done) t++; // idle until next arrival
    }

    printf("\n--- Round Robin (TQ=%d) ---\n", tq);
    print_table(p,n);
    printf("Avg TAT = %.2f, Avg WT = %.2f\n", tot_tat/n, tot_wt/n);
    free(p);
}

int main(void){
    int n;
    printf("Number of processes: "); if(scanf("%d",&n)!=1 || n<=0) return 0;
    Proc *p = malloc(sizeof(Proc)*n);
    read_procs(p,n);

    int choice;
    printf("\nChoose: 1) SJF Preemptive  2) Round Robin\nEnter: "); scanf("%d",&choice);
    if(choice==1){
        Proc *q = malloc(sizeof(Proc)*n);
        for(int i=0;i<n;i++) q[i]=p[i];
        sjf_preemptive(q,n);
        free(q);
    } else if(choice==2){
        int tq; printf("Time Quantum: "); scanf("%d",&tq);
        if(tq<=0) { printf("Invalid TQ\n"); free(p); return 0; }
        round_robin(p,n,tq);
    } else printf("Invalid choice\n");

    free(p);
    return 0;
}

