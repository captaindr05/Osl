#include <stdio.h>
#define MAX 20

int isPresent(int frames[], int n, int page)  // check if page is present
{
    for(int i = 0; i < n; i++)
        if(frames[i] == page)
            return 1;  // page hit
    return 0;  // page fault
}

void printFrames(int frames[], int n)  // print current frame contents
{
    for(int i = 0; i < n; i++)
    {
        if(frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void fifo(int pages[], int n, int frameSize)
{
    int frames[MAX], faults = 0, index = 0;

    for(int i = 0; i < frameSize; i++)
        frames[i] = -1;  // initially all empty

    printf("\nFIFO Page Replacement\n");
    printf("Page\tFrames\t\tPage Fault\n");

    for(int i = 0; i < n; i++)
    {
        if(!isPresent(frames, frameSize, pages[i])) // if not present
        {
            frames[index] = pages[i]; // replace oldest
            index = (index + 1) % frameSize;
            faults++;
            printf("%d\t", pages[i]);
            printFrames(frames, frameSize);
            printf("\tYes\n");
        }
        else
        {
            printf("%d\t", pages[i]);
            printFrames(frames, frameSize);
            printf("\tNo\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", faults);
}

int main()
{
    int pages[MAX], n, frameSize;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frameSize);

    fifo(pages, n, frameSize);
    return 0;
}

