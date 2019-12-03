#pragma once

#include <stdio.h>

#define BUF_SIZE 2048

char *getMessage(int socket);

int sendMessage(int socket, const char *message);

int sendFile(FILE *filePointer, int socket);

void sendDirectory(int sockfd, const char** dirTable);