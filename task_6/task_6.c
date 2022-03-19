#include <stdio.h>
#include <dirent.h>

int printDir(const char *dirname)
{
    DIR *dir;
    printf("Contents of %s:\n", dirname);
    if ((dir = opendir(dirname)) == NULL) {
        perror("Directory opening error.\n");
        return -1;
    }
    struct dirent *dirent;
    while ((dirent = readdir(dir)) != NULL) {
        printf("    %s\n", dirent->d_name);
    }
    if (closedir(dir)) {
        perror("Error during attempt to close directory.\n");
        return -1;
    }

    return 0;
}

int main()
{
    int errorCode = 0;
    errorCode = printDir("./");
    if (errorCode < 0)
    {
    	return errorCode;
    }
    errorCode = printDir("/");

    return errorCode;
}
