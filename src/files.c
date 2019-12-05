#pragma once

#include "files.h"
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

long getFileSize(FILE* filePtr) {
    long prev=ftell(filePtr);
    fseek(filePtr, 0L, SEEK_END);
    long sz=ftell(filePtr);
    fseek(filePtr,prev,SEEK_SET);
    return sz;
}

FILE* getFilePtrFromDir(const struct File_d** dir, const unsigned int num){
    char* path = malloc(sizeof(char)*BUF_SIZE);
    memset(path, 0, BUF_SIZE);
    sprintf(path, "/home/marcin/Downloads/%s", dir[num-1]->name);
    FILE* ptr = fopen(path, "r");
    return ptr;
}