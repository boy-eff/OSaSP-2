#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Function %s has 2 parameters\n", argv[0]);
        fprintf(stderr, "1.filename\n");
        fprintf(stderr, "2.group size\n");
        return -1;
    }

    int groupSize = atoi(argv[2]);
    if (groupSize < 0) {
        fprintf(stderr, "Group size must be >= 0\n");
        return -1;
    }
    
    FILE *file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        perror("File opening error: ");
        return -1;
    }

    char ch;
    if (groupSize > 0)
    {
        while (ch != EOF)
        {
            for (int i = 0; i < groupSize; i++)
            {
                ch = 0;
                while ((ch = getc(file)) != EOF && ch != '\n')
                {
                    putc(ch, stdout);
                }
                if (ch == EOF)
                {
                    break;
                }
            }
            fgetc(stdin);
        }
    }
    else 
    {
        while ((ch = getc(file)) != EOF)
        {
            putc(ch, stdout);
        }
    }
    
    
    
    if (fclose(file) == EOF) {
        perror("File closing error: ");
        return -1;
    }

    return 0;
}
