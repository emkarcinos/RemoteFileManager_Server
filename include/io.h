#pragma once

#define BUF_SIZE 2048

char *getMessage(int socket);

int sendMessage(int socket, const char *message);

char **splitMessage(const char *message, int segmentSize);