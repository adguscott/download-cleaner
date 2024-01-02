/*
 * download-cleaner:
 * a simple program to move files of types to folders specified in <config.h>
*/
 
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "common.h"
#include "config.h"
#include "download-cleaner.h"

int
main(void) {
    if (!validate_directories()) {
        fprintf(stderr, "Missing valid directories");
        return 1;
    }
   
    DIR *directory = NULL;
    if ((directory = opendir(downloaddir)) == NULL) {
        fprintf(stderr, "Failed to open directory: %s = %s\n", downloaddir, strerror(errno));
        return 1;
    }

    struct dirent *file = NULL;
    struct DirType *dirtype = NULL;

    while ((file = readdir(directory)) != NULL) {
        if (file->d_type == DT_DIR) // ignore directories
            continue;
        
        char filename[256] = {0};
        strcpy(filename, file->d_name);
        
        char *ext = (strrchr(filename, '.')) + 1;
        dirtype = get_dir(ext);

        if (dirtype == NULL) {
            printf("Unknown filetype: %s\n", ext);
            continue;
        }
        
        struct FilePath *filepath = get_filepath(filename, dirtype);
        
        printf("%s -> %s", filepath->oldpath, filepath->newpath); 

        if (rename(filepath->oldpath, filepath->newpath) == 0) {
            printf(" ✓\n");
        } else {
            fprintf(stderr, " ×:  %s\n", strerror(errno));
        }

        free(filepath);
    }
    
    if (closedir(directory) == -1) {
       fprintf(stderr, "Failed to close directory: %s - %s", downloaddir, strerror(errno));
       return 1;
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
validate_directories(void) {
    int valid = 1;
    for (int i = 0; i < dirtypes_length; i++) {
        if (!directory_valid(dirtypes[i].dir)) {
            valid = 0;
            fprintf(stderr, "Invalid directory: %s\n", dirtypes[i].dir);
        }
    }
    return valid;
}

struct DirType
*get_dir(char ext[]) {
    for (int i = 0; i < dirtypes_length; i++) {
        for (int j = 0; dirtypes[i].types[j] != NULL; j++) {
            if (strcmp(dirtypes[i].types[j], ext) == 0) {
                return &dirtypes[i];
            }
        }
    }
    
    return NULL;
}

struct FilePath 
*get_filepath(char *filename, struct DirType *dirtype) {
    struct FilePath *filepath = malloc(sizeof(struct FilePath));

    sprintf(filepath->oldpath, "%s/%s", downloaddir, filename);
    sprintf(filepath->newpath, "%s/%s", dirtype->dir, filename);

    return filepath;
}

