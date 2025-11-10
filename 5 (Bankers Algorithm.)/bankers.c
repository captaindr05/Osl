#include <stdio.h>

int main() {
    int p, r;
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &r);

    int alloc[p][r], max[p][r], need[p][r], avail[r];
    int done[p], safe[p];

    printf("Enter Allocation matrix (%dx%d):\n", p, r);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum matrix (%dx%d):\n", p, r);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources (%d):\n", r);
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < p; i++) {
        done[i] = 0;
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!done[i]) {
                int canRun = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    safe[count++] = i;
                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];
                    done[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("No safe sequence exists.\n");
            return 0;
        }
    }

    printf("\nSafe sequence is: ");
    for (int i = 0; i < p; i++)
        printf("P%d ", safe[i]);
    printf("\n");

    printf("Available resources after completion: ");
    for (int i = 0; i < r; i++)
        printf("%d ", avail[i]);
    printf("\n");

    return 0;
}

