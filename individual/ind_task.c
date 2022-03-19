#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int minSize;
int maxSize;
FILE *out;
int counter = 0;
int errorNum = 0;

int closeFile(FILE *f) {
    int error = 0;
    if (fclose(f) == EOF) {
        perror("File closing error: ");
        error = -1;
    }
    return error;
}

int closeDir(DIR *d) {
    int error = 0;
    if ((closedir(d)) == -1)
    {
        perror("Directory closing error:");
        error = -1;
    }
    return error;
}

void nextdir(char folder[255])
{
    DIR *dfd;
    struct dirent *dp;
    
    if ((dfd = opendir(folder)) == NULL)
    {
        perror("Directory opening error:");
        errorNum = -1;
        return;
    }
    printf("Открытие папки %s \n", folder);
    while ((dp = readdir(dfd)) != NULL && (errorNum >= 0))
        if (dp->d_type != DT_DIR) 
        {
            counter++;
            char path[MAXNAMLEN];

            strcpy(path, folder);
            strcat(path, "/");
            strcat(path, dp->d_name);

            FILE *file;
            if ((file = fopen(path, "r")) == NULL)
            {
                perror("File opening error:");
                errorNum = -1;
                closeDir(dfd);
                return;
            }
            struct stat fileStat;
            if (stat(path, &fileStat) < 0)
            {
                perror("Stat receiving error: ");
                closeDir(dfd);
                closeFile(file);
                errorNum = -1;
                return;
            }

            if (fileStat.st_size > minSize && fileStat.st_size < maxSize)
            {   
                char fullPath[255];
                fprintf(out,"full path: %s\nfile: %s\nsize: %d\n",realpath(folder, fullPath), dp->d_name, fileStat.st_size);
            }
            printf("%s\n", dp->d_name); 
            if ((fclose(file)) == EOF)
            {
                perror("File closing error:");
                closeDir(dfd);
                errorNum = -1;
                return;
            }
        }
        else
            if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)) && errorNum >= 0) {
                char next[255];
                strcpy(next, folder);
                strcat(next, "/");
                nextdir(strcat(next, dp->d_name));
            }
    if ((closedir(dfd)) == -1)
    {
        perror("Directory closing error:");
        errorNum = -1;
        return;
    }
 
}


int main(int argc, char *argv[]) 
{
    if (argc != 5)
    {
        fprintf(stderr, "Function %s has 4 parameters:\n", argv[0]);
        fprintf(stderr, "1: Path to directory\n");
        fprintf(stderr, "2: Min size of files\n");
        fprintf(stderr, "3: Max size of files\n");
        fprintf(stderr, "4: File to store information\n");
        return -1;
    }
    char *dirPath = argv[1];   
    minSize = atoi(argv[2]);
    maxSize = atoi(argv[3]);
    char *fileName = argv[4];
    if ((out = fopen(fileName, "w")) == NULL)
    {
        perror("File opening error:");
        return -1;
    }
    nextdir(dirPath);
    if ((fclose(out)) == EOF)
    {
        perror("File closing error:");
    }
    printf("Files amount: %d", counter);
    printf("\n");
}
