int delete_files(int days);
int move_files(void);
void print_missing_args(void);
void print_usage(void);
int validate_directories(void);
struct DirType *get_dir(char ext[]);
struct FilePath *get_filepath(char *filename, struct DirType *dirtype);

