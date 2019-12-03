#pragma once

#include <stdio.h>

#include "files.h"

char *getMessage(int socket);

int sendMessage(int socket, const char *message);

int sendFile(FILE *filePointer, int socket);

void sendDirectory(int sockfd, const struct File_d** dirTable);

void sendFileSize(int sockfd, FILE* filePtr);