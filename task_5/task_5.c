#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


int closeFiles(FILE *src, FILE *dest)
{
    int error = 0;
    if (fclose(src) == EOF) {
        perror("File closing error: ");
    }
    if (fclose(dest) == EOF) {
        perror("File closing error: ");
    }
    return error;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Function %s has 2 parameters\n", argv[0]);
        fprintf(stderr, "1.Source file\n");
        fprintf(stderr, "2.Destination file\n");
        return -1;
    }



    FILE *src;
    char *srcName = argv[1];
    FILE *dest; 
    char *destName = argv[2];
    if ((src = fopen(srcName, "r")) == NULL) {
        perror("File opening error: ");
        return -1;
    }
    if ((dest = fopen(destName, "w")) == NULL) {
        perror("File opening error: ");
        return -1;
    }

    struct stat accessRights;
    if (stat(srcName, &accessRights)) {
        perror("Information accessing  error: ");
        closeFiles(src, dest);
        return -1;
    }
    if (chmod(destName, accessRights.st_mode)) {
        perror("Rights receiving error:");
        closeFiles(src, dest);
        return -1;
    }

    char ch;
    while ((ch = getc(src)) != EOF) {
        if (putc(ch, dest) == EOF) {
            perror("File writing error: ");   
            break;
        }
    }

    return closeFiles(src, dest);
}
