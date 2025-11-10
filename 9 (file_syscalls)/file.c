#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd, n;
    char writebuf[100], readbuf[100];

    /* ---- OPEN + WRITE ---- */
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if(fd < 0){
        perror("open");
        exit(1);
    }

    printf("Enter text to write into file:\n");
    fgets(writebuf, sizeof(writebuf), stdin);

    n = write(fd, writebuf, strlen(writebuf));
    if(n < 0){
        perror("write");
        close(fd);
        exit(1);
    }
    printf("Data written to file successfully.\n");

    /* ---- SET POINTER TO BEGINNING ---- */
    lseek(fd, 0, SEEK_SET);

    /* ---- READ ---- */
    n = read(fd, readbuf, sizeof(readbuf)-1);
    if(n < 0){
        perror("read");
        close(fd);
        exit(1);
    }
    readbuf[n] = '\0';  // null terminate

    printf("Data read from file:\n%s\n", readbuf);

    /* ---- CLOSE ---- */
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}

