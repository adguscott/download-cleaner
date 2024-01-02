/*
 * Amend <downloaddir> & <dirtypes> as necessary.
 * struct DirType found in <common.h>
 */

static const char downloaddir[25] = "/home/adam/Downloads";

static const int dirtypes_length = 5;
struct DirType dirtypes[5] = {
    { "/home/adam/Pictures", { "png", "jpg", "jpeg", "gif", NULL } },
    { "/home/adam/Music", { "mp3", "wav", "flac", "ogg", NULL } },
    { "/home/adam/Videos", { "mp4", "mov", "avi", "mkv", NULL } },
    { "/home/adam/Books", { "pdf", "epub", "mobi", "azw", NULL } },
    { "/home/adam/Documents", { "docx", NULL, NULL, NULL, NULL } },
};
