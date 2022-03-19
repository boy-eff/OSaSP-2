#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    const EXIT_NUM = 6;
    if (argc != 2) {
        fprintf(stderr, "Function %s has 1 parameter\n", argv[0]);
        fprintf(stderr, "1.filename\n");
        return -1;
    }

    printf("Type ^F to exit.\n");
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("File opening error: ");
        return -1;
    }

    while ((ch = getc(stdin)) != EXIT_NUM) {
        if (fputc(ch, file) == EOF) {
            perror("File writing error: ");
            break;
        }
    }

    if (fclose(file) == EOF) {
        perror("File closing error: ");
        return -1;
    }

    return 0;
}
