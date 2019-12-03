#pragma once

#include "files.h"
#include "io.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File_d** getDirectory(const char *path) {
    struct File_d** dirTable = malloc(sizeof(struct File_d*)*BUF_SIZE);
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        int num = 0;
        while ((ent = readdir(dir)) != NULL) {
            dirTable[num] = malloc(sizeof(struct File_d));
            dirTable[num]->id=num + 1;
            memcpy(dirTable[num]->name, ent->d_name, strlen(ent->d_name));
            num++;
        }
        closedir(dir);
    }
    return dirTable;
}

FILE* getFilePtrFromDir(const char** dir, const unsigned short num){
    FILE* ptr = malloc(sizeof(FILE));

}