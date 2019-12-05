#pragma once

#include <stdio.h>

#include "files.h"

int readInt(int socket);

int sendFile(FILE *filePointer, int socket);

void sendDirectory(int sockfd, const struct File_d** dirTable);

void sendFileSize(int sockfd, FILE* filePtr);

char* composePacket(char type, int len, const char* message);

int getPacketSize(const char* packet);

void sendPacket(int sockfd, const char* packet);

void sendString(int sockfd, const char* message);

void sendEndOfService(int sockfd);

void askForInput(int sockfd);

