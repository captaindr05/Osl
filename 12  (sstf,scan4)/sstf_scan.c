#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int SSTF();
int SCAN();

int main()
{
    int ch, YN = 1;
    do
    {
        printf("\n********* MENU *********\n");
        printf("\n1. SSTF\n2. SCAN\n3. EXIT\n");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            SSTF();
            break;
        case 2:
            SCAN();
            break;
        case 3:
            exit(0);
        default:
            printf("\nInvalid choice!\n");
        }

        printf("\nDo you want to continue (1/0): ");
        scanf("%d", &YN);
    } while (YN == 1);

    return 0;
}

/* ---------- SSTF ---------- */
int SSTF()
{
    int Rq[100], n, TotalHeadMovement = 0, initial, count = 0, i, j;
    printf("\nEnter no. of requests: ");
    scanf("%d", &n);
    printf("Enter the request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &Rq[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    while (count != n)
    {
        int min = 1000, d, index;
        for (i = 0; i < n; i++)
        {
            d = abs(Rq[i] - initial);
            if (min > d)
            {
                min = d;
                index = i;
            }
        }
        TotalHeadMovement += min;
        initial = Rq[index];
        Rq[index] = 1000;
        count++;
    }

    printf("Total head movement (SSTF) = %d\n", TotalHeadMovement);
    return 0;
}

/* ---------- SCAN ---------- */
int SCAN()
{
    int Rq[100], n, i, j, TotalHeadMovement = 0, initial, size, move;
    printf("\nEnter no. of requests: ");
    scanf("%d", &n);
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &Rq[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    /* sort request sequence */
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (Rq[j] > Rq[j + 1])
            {
                int temp = Rq[j];
                Rq[j] = Rq[j + 1];
                Rq[j + 1] = temp;
            }

    int index;
    for (i = 0; i < n; i++)
        if (initial < Rq[i])
        {
            index = i;
            break;
        }

    if (move == 1) /* move toward higher tracks first */
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(Rq[i] - initial);
            initial = Rq[i];
        }
        TotalHeadMovement += abs((size - 1) - initial);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(Rq[i] - initial);
            initial = Rq[i];
        }
    }
    else /* move toward lower tracks first */
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(Rq[i] - initial);
            initial = Rq[i];
        }
        TotalHeadMovement += abs(initial - 0);
        initial = 0;
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(Rq[i] - initial);
            initial = Rq[i];
        }
    }

    printf("Total head movement (SCAN) = %d\n", TotalHeadMovement);
    return 0;
}

