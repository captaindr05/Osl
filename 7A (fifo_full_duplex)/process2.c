// process2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUF 1024

void analyze_text(const char *s, int *chars, int *words, int *lines) {
    int i=0, inword=0;
    *chars = *words = *lines = 0;
    while(s[i] != '\0') {
        unsigned char c = s[i];
        (*chars)++;
        if(c == '\n') (*lines)++;
        if(isspace(c)) inword = 0;
        else if(!inword) { inword = 1; (*words)++; }
        i++;
    }
    if(*chars > 0 && s[i-1] != '\n') (*lines)++;
}

int main() {
    char buf[BUF];
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    /* read from fifo1 */
    int fdr = open(FIFO1, O_RDONLY);
    if(fdr < 0) { perror("open fifo1 for read"); exit(1); }
    ssize_t n = read(fdr, buf, sizeof(buf)-1);
    if(n <= 0) { close(fdr); exit(0); }
    buf[n] = '\0';
    close(fdr);

    /* analyze and write to file */
    int chars, words, lines;
    analyze_text(buf, &chars, &words, &lines);

    FILE *fp = fopen("analysis.txt", "w");
    if(!fp) { perror("fopen"); exit(1); }
    fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(fp);

    /* read file contents */
    fp = fopen("analysis.txt", "r");
    if(!fp) { perror("fopen-read"); exit(1); }
    char out[BUF]; size_t r = fread(out, 1, sizeof(out)-1, fp);
    out[r] = '\0';
    fclose(fp);

    /* write result to fifo2 */
    int fdw = open(FIFO2, O_WRONLY);
    if(fdw < 0) { perror("open fifo2 for write"); exit(1); }
    write(fdw, out, strlen(out) + 1);
    close(fdw);

    return 0;
}

