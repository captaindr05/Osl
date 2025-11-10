// process1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUF 1024

int main() {
    char input[BUF], buf[BUF];
    /* create FIFOs if not exist */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter sentence (end with Enter):\n");
    if(!fgets(input, sizeof(input), stdin)) input[0]='\0';

    /* write sentence to fifo1 */
    int fdw = open(FIFO1, O_WRONLY);
    if(fdw < 0) { perror("open fifo1 for write"); exit(1); }
    write(fdw, input, strlen(input) + 1);
    close(fdw);

    /* read response from fifo2 */
    int fdr = open(FIFO2, O_RDONLY);
    if(fdr < 0) { perror("open fifo2 for read"); exit(1); }
    ssize_t n = read(fdr, buf, sizeof(buf)-1);
    if(n > 0) { buf[n] = '\0'; printf("\n--- Result from Process 2 ---\n%s\n", buf); }
    else printf("No response received.\n");
    close(fdr);

    /* cleanup FIFOs (optional) */
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}

