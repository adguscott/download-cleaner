int directory_valid(char *dirname);
int validate_directories(void);
struct DirType *get_dir(char ext[]);
struct FilePath *get_filepath(char *filename, struct DirType *dirtype);

