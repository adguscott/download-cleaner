/*
 * download-cleaner:
 * a simple program to move files of types to folders specified in <config.h>
*/
 
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "config.h"
#include "download-cleaner.h"

int
main(int argc, char *argv[]) {
    int opt = 0, success_status = 0;
    
    while((opt = getopt(argc, argv, "md:")) != -1) {
        switch(opt) {
            case 'm':
                success_status = move_files();
                break;
            case 'd':
                int days = atoi(optarg);
                success_status = delete_files(days);
                break;
        }
    }
    
    if (argc == 1) {
        print_usage();
    }
    
    return success_status;
}

int
delete_files(int days) {
    DIR *directory = NULL;
    if ((directory = opendir(downloaddir)) == NULL) {
        fprintf(stderr, "Failed to open directory: %s, Error: %s\n", downloaddir, strerror(errno));
        return 1;
    }

    struct dirent *file = NULL;
    while ((file = readdir(directory)) != NULL) {
        char filename[256] = {0};
        strcpy(filename, file->d_name);

        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
            continue;
        }
        
        char *filepath = combine_path(downloaddir, filename);
        int fdays = file_age_days(filepath);

        if (fdays == -1) {
            fprintf(stderr, "Error error retrieving age of file %s. Skipping.\n", filename);
            free(filepath);
            continue;
        }

        if (days >= fdays) {
            if ((remove(filepath)) == -1) {
                fprintf(stderr, "Failed to delete file/directory: %s, Error:  %s\n", filename, strerror(errno));
            } else {
                printf("× %s\n", filename);
            }
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
move_files(void) {
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
    char **types;
    int j = 0;
    for (int i = 0; i < dirtypes_length; i++) {
        types = string_split(dirtypes[i].types, ',');
        while ((types[j]) != NULL) {
            if (strcmp(types[j++], ext) == 0) {
                return &dirtypes[i];
            }
        }
        free(types);
        j = 0;
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

void
print_usage(void) {
    printf("usage: download-cleaner <option>\n");
    printf("Clean up your downloads folder, program can move files to directories specified or delete files with atime older than specified days.\n\n");
    printf("-m\t\tMove files from the Downloads directory to directories specified in config.h\n");
    printf("-d=DAYS\t\tDelete all files from the Downloads directory with atime >= DAYS\n");
}
