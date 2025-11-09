#include <stdio.h>
#include <stdlib.h>

#define MAX 30

int pages[MAX], n, frames;

void enterData() {
    do {
        printf("Enter number of frames (minimum 3): ");
        scanf("%d", &frames);
        if (frames < 3) printf("Frame size must be at least 3!\n");
    } while (frames < 3);

    printf("Enter length of page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
}

// ---------- OPTIMAL ----------
void optimal() {
    int frame[MAX], faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++)
            if (frame[j] == pages[i]) { found = 1; break; }

        if (!found) {
            if (i < frames) frame[i] = pages[i];
            else {
                int farthest = -1, pos = -1;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++)
                        if (frame[j] == pages[k]) break;
                    if (k == n) { pos = j; break; }
                    if (k > farthest) { farthest = k; pos = j; }
                }
                if (pos == -1) pos = 0;
                frame[pos] = pages[i];
            }
            faults++;
        }

        printf("\nFor %d: ", pages[i]);
        for (int k = 0; k < frames && frame[k] != -1; k++)
            printf("%d ", frame[k]);
    }
    printf("\nTotal number of page faults: %d\n", faults);
}

// ---------- LRU ----------
void lru() {
    int frame[MAX], count[MAX], faults = 0;
    for (int i = 0; i < frames; i++) { frame[i] = -1; count[i] = 0; }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++)
            if (frame[j] == pages[i]) { found = 1; count[j] = i; break; }

        if (!found) {
            int min = 0;
            for (int j = 1; j < frames; j++)
                if (count[j] < count[min]) min = j;
            frame[min] = pages[i];
            count[min] = i;
            faults++;
        }

        printf("\nFor %d: ", pages[i]);
        for (int k = 0; k < frames && frame[k] != -1; k++)
            printf("%d ", frame[k]);
    }
    printf("\nTotal number of page faults: %d\n", faults);
}

int main() {
    int ch;
    while (1) {
        printf("\n*** PAGE REPLACEMENT ALGORITHMS (LRU & OPTIMAL) ***");
        printf("\n1. Enter Data\n2. LRU\n3. Optimal\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: enterData(); break;
            case 2: lru(); break;
            case 3: optimal(); break;
            case 4: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }
}

