#include <stdio.h>
#include <stdlib.h>

#define MAXP 100
#define MAXF 20

int pages[MAXP], nPages = 0, nFrames = 0;

int hit(int frames[], int f, int p) {
    for (int i = 0; i < f; i++) if (frames[i] == p) return i;
    return -1;
}

void printFrames(int frames[], int f) {
    for (int i = 0; i < f; i++)
        (frames[i] == -1) ? printf("- ") : printf("%d ", frames[i]);
}

void enterData() {
    do {
        printf("Enter number of frames (min 3): ");
        scanf("%d", &nFrames);
        if (nFrames < 3) printf("Frame size must be at least 3!\n");
    } while (nFrames < 3 || nFrames > MAXF);

    printf("Enter length of page reference string: ");
    scanf("%d", &nPages);
    printf("Enter the page reference string: ");
    for (int i = 0; i < nPages; i++) scanf("%d", &pages[i]);
}

/* ---------- FCFS (FIFO) ---------- */
void fcfs() {
    if (nFrames < 3 || nPages == 0) { printf("Enter data first!\n"); return; }

    int frames[MAXF], faults = 0, front = 0;
    for (int i = 0; i < nFrames; i++) frames[i] = -1;

    printf("\nFCFS (FIFO) Page Replacement\nPage\tFrames\t\tFault\n");
    for (int i = 0; i < nPages; i++) {
        int pos = hit(frames, nFrames, pages[i]);
        if (pos == -1) {
            frames[front] = pages[i];
            front = (front + 1) % nFrames;
            faults++;
            printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tYes\n");
        } else {
            printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tNo\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

/* ---------- LRU ---------- */
void lru() {
    if (nFrames < 3 || nPages == 0) { printf("Enter data first!\n"); return; }

    int frames[MAXF], timeStamp[MAXF], faults = 0, clk = 0;
    for (int i = 0; i < nFrames; i++) { frames[i] = -1; timeStamp[i] = -1; }

    printf("\nLRU Page Replacement\nPage\tFrames\t\tFault\n");
    for (int i = 0; i < nPages; i++) {
        clk++;
        int pos = hit(frames, nFrames, pages[i]);
        if (pos != -1) {
            timeStamp[pos] = clk; /* refresh recency */
            printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tNo\n");
            continue;
        }

        /* find empty slot first */
        int place = -1;
        for (int j = 0; j < nFrames; j++) if (frames[j] == -1) { place = j; break; }

        if (place == -1) { /* replace least recently used */
            int lruIdx = 0;
            for (int j = 1; j < nFrames; j++)
                if (timeStamp[j] < timeStamp[lruIdx]) lruIdx = j;
            place = lruIdx;
        }

        frames[place] = pages[i];
        timeStamp[place] = clk;
        faults++;
        printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tYes\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

/* ---------- Optimal ---------- */
void optimal() {
    if (nFrames < 3 || nPages == 0) { printf("Enter data first!\n"); return; }

    int frames[MAXF], faults = 0;
    for (int i = 0; i < nFrames; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement\nPage\tFrames\t\tFault\n");
    for (int i = 0; i < nPages; i++) {
        int pos = hit(frames, nFrames, pages[i]);
        if (pos != -1) {
            printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tNo\n");
            continue;
        }

        /* empty slot first */
        int place = -1;
        for (int j = 0; j < nFrames; j++) if (frames[j] == -1) { place = j; break; }

        if (place == -1) {
            /* choose the page used farthest in future (or never) */
            int farIdx = -1, farDist = -1;
            for (int j = 0; j < nFrames; j++) {
                int k;
                for (k = i + 1; k < nPages; k++) if (frames[j] == pages[k]) break;
                int dist = (k == nPages) ? 1e9 : k; /* never used => best */
                if (dist > farDist) { farDist = dist; farIdx = j; }
            }
            place = farIdx;
        }

        frames[place] = pages[i];
        faults++;
        printf("%d\t", pages[i]); printFrames(frames, nFrames); printf("\tYes\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int ch;
    while (1) {
        printf("\n--- PAGE REPLACEMENT (min frames = 3) ---\n");
        printf("1. Enter Data\n2. FCFS (FIFO)\n3. LRU\n4. Optimal\n5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) return 0;

        switch (ch) {
            case 1: enterData(); break;
            case 2: fcfs(); break;
            case 3: lru(); break;
            case 4: optimal(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}


