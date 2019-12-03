#pragma once

#include <stdio.h>
#include "settings.h"

struct File_d {
    int id;
    char name[BUF_SIZE];
};

struct File_d** getDirectory(const char* path);

FILE* getFilePtrFromDir(const char** dir, unsigned short num);