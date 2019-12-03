#pragma once

#include "files.h"
#include "io.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

char** getDirectory(const char *path) {
    char** dirTable = malloc(sizeof(char*)*BUF_SIZE);
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        int num = 0;
        while ((ent = readdir(dir)) != NULL) {
            dirTable[num] = malloc(sizeof(char)*BUF_SIZE);
            sprintf(dirTable[num], "%d: %s", num+1, ent->d_name);
            num++;
        }
        closedir(dir);
    }
    return dirTable;
}