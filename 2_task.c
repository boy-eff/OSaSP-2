#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Function ");
        fprintf(stderr, argv[0]);
        fprintf(stderr, " has 1 parameter\n");
        fprintf(stderr, "1.filename\n");
        return -1;
    }

    int fDescriptor;
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("File opening error\n");
        return -1;
    }

    char ch;
    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }

    if (fclose(file) == EOF) {
        perror("File closing error\n");
        return -1;
    }

    return 0;
}
