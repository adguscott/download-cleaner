/*
 * Amend <downloaddir> & <dirtypes> as necessary.
 * struct DirType found in <common.h>
 */

static const char downloaddir[25] = "/home/user/Downloads";

static const int dirtypes_length = 5;
struct DirType dirtypes[5] = {
    { "/home/user/Pictures", "png,jpg,jpeg,gif" },
    { "/home/user/Music", "mp3,wav,flac,ogg" },
    { "/home/user/Videos", "mp4,mov,avi,mkv" },
    { "/home/user/Books", "pdf,epub,mobi,azw" },
    { "/home/user/Documents", "docx" },
};
