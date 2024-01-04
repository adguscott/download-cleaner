#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stddef.h>

struct FilePath {
    char oldpath[256];
    char newpath[256];
};

struct DirType {
    char dir[25];
    char types[100];
};

char**
string_split(char *string, char delimiter) {
    int const bufsize = 1024;
    int wcount = 0;
    
    char *stringcpy = malloc(strlen(string));
    strcpy(stringcpy, string);
    
    char **splitwords = malloc(bufsize);

    char *splitword = strtok(stringcpy, &delimiter);    
    splitwords[wcount++] = splitword;
    
    while((splitword = strtok(NULL, &delimiter)) != NULL) {
	    splitwords[wcount++] = splitword;
    }
    
    if ((splitwords = realloc(splitwords, (wcount * sizeof(char**)) + 1)) == NULL) 
	    return NULL;

    splitwords[wcount] = NULL;
    free(stringcpy);

    return splitwords;
}

int file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

int dir_exists(const char *dirname) {
    DIR *dir;
    if (file_exists(dirname)) {
       if ((dir = opendir(dirname)) != NULL) {
           closedir(dir);
           return 1;
       }
    }

    return 0;
}
