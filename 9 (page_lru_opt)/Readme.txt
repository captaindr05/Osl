gcc page_replacement.c -o page_replacement

./page_replacement



*** PAGE REPLACEMENT ALGORITHMS (LRU & OPTIMAL) ***
1. Enter Data
2. LRU
3. Optimal
4. Exit
Enter your choice: 1
Enter number of frames (minimum 3): 3
Enter length of page reference sequence: 7
Enter the page reference sequence: 1 2 3 4 1 2 5

*** PAGE REPLACEMENT ALGORITHMS (LRU & OPTIMAL) ***
1. Enter Data
2. LRU
3. Optimal
4. Exit
Enter your choice: 2

For 1: 1
For 2: 1 2
For 3: 1 2 3
For 4: 4 2 3
For 1: 4 1 3
For 2: 2 1 4
For 5: 5 2 4
Total number of page faults: 7

*** PAGE REPLACEMENT ALGORITHMS (LRU & OPTIMAL) ***
1. Enter Data
2. LRU
3. Optimal
4. Exit
Enter your choice: 3

For 1: 1
For 2: 1 2
For 3: 1 2 3
For 4: 4 2 3
For 1: 1 4 3
For 2: 2 1 4
For 5: 5 2 4
Total number of page faults: 7

