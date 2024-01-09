#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

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

    return splitwords;
}

char
*combine_path(const char *path_1, const char *path_2) {
    char *path = malloc(strlen(path_1) + strlen(path_2) + 1);

    sprintf(path, "%s/%s", path_1, path_2);

    return path;
}

int file_exists(const char *filepath) {
    return access(filepath, F_OK) == 0;
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

int
directory_valid(char *dirname) {
    if (dir_exists(dirname)) {
        return 1;
    } else {
        fprintf(stderr, "%s does not exist\n", dirname); 
        return 0;
    }
}

int
seconds_to_days(int seconds) {
    if (seconds <= 0) {
        return -1;
    }
    
    return (int)(seconds / 86400);
}

int
file_age_days(const char *filepath) {
    struct stat fstat;

    if (stat(filepath, &fstat) == - 1) {
        return -1;
    }

    time_t now = time(NULL);

    int seconds = difftime(now, fstat.st_atime);
    
    return seconds_to_days(seconds);
}
