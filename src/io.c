#pragma once

#include <sys/socket.h>
#include <string.h>
#include "io.h"
#include "log.h"

char *getMessage(const int socket) {
    static char msg[BUF_SIZE];
    memset(msg, '\0', BUF_SIZE * sizeof(char));
    log_info("Waiting for message...");
    if (recv(socket, msg, BUF_SIZE, 0) <= 0) {
        log_warn("Received an empty message");
        return "";
    }
    log_info("Message: %s", msg);
    return msg;
}

int sendMessage(const int socket, const char *message) {
    log_info("Sending a message...");
    int receivedBytes = send(socket, message, BUF_SIZE, 0);
    if (receivedBytes < 0)
        log_error("An error has occurred during sending.");
    else
        log_info("Message sent.");
    return receivedBytes;
}

int sendFile(FILE *filePointer, const int socket) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE * sizeof(char));
    int readBytes;
    while ((readBytes = fread(buffer, sizeof(char), BUF_SIZE, filePointer)) > 0) {
        if (ferror(filePointer)) {
            log_error("Error opening the file.");
            return -1;
        }
        if (send(socket, buffer, readBytes, 0) < 0) {
            log_error("An error has occurred during file sending.");
            return -1;
        }
        memset(buffer, 0, BUF_SIZE * sizeof(char));
    }
    return 0;
}

void sendDirectory(const int sockfd, const struct File_d** dirTable){
    char buffer[BUF_SIZE];
    for(int i = 0; dirTable[i] != NULL; i++) {
        sprintf(buffer, "%d: %s\n", dirTable[i]->id, dirTable[i]->name);
    }
    sendMessage(sockfd, buffer);
}