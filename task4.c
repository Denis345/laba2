#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>


int printStr(FILE *inputFile, FILE *outputFile)
{
    int ch = getc(inputFile);
    while (ch != EOF && ch != '\n') {
        if (putc(ch, outputFile) == EOF)
            return EOF;
        ch = getc(inputFile);
    }
    if (ch == '\n' && putc(ch, outputFile) == EOF)
        return EOF;
    return ch;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "You should enter 2 parameters:\n");
        fprintf(stderr, "    First - filename\n");
        fprintf(stderr, "    Second - group size\n");
        return -1;
    }

    
    char *str, *endptr;
    long val;
    str = argv[2];
    //       base = (argc > 2) ? atoi(argv[2]) : 10;

           errno = 0;    /* To distinguish success/failure after call */
           val = strtol(str, &endptr, 0);

           /* Check for various possible errors */

           if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
                   || (errno != 0 && val == 0)) {
               perror("strtol");
               exit(EXIT_FAILURE);
           }

           if (endptr == str) {
               fprintf(stderr, "No digits were found\n");
               exit(EXIT_FAILURE);
           }

    int groupSize = val;
    
    
    
    if (groupSize < 0) {
        fprintf(stderr, "You entered wrong group size. It should be >=0\n");
        return -1;
    }
    FILE *file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        perror("Error during file opening attempt\n");
        return -2;
    }

    int eof = 1;
    int counter;
    while (eof != EOF) {
        counter = 0;
        do {
            eof = printStr(file, stdout);
        } while (eof != EOF && ++counter != groupSize);
        if (eof != EOF) {
            printf("Press any key\n");
            while (getchar() != '\n');
        }
    }
    
    if (fclose(file) == EOF) {
        perror("Error during file closing attempt. May cause loss of data.\n");
        return -3;
    }

    return 0;
}
