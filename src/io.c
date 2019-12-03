#pragma once

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include "io.h"
#include "log.h"
#include "protocol.h"

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

int sendMessage(int socket, const char *message) {
    char* temp = getMessage(socket);
    if(strcmp(temp, C_ACK)==0){
        log_info("Sending a message...");
        int receivedBytes = send(socket, message, 1024, 0);
        if (receivedBytes <= 0)
            log_error("An error has occurred during sending.");
        else
            log_info("Message sent.");
        return receivedBytes;
    } else {
        return -1;
    }
}

int sendFile(FILE *filePointer, const int socket) {
    sendMessage(socket, FILE_START);
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE * sizeof(char));
    int readBytes;
    while ((readBytes = fread(buffer, sizeof(char), BUF_SIZE, filePointer)) > 0) {
        if (ferror(filePointer)) {
            sendMessage(socket, FILE_ERR);
            log_error("Error opening the file.");
            return -1;
        }
        if (send(socket, buffer, readBytes, 0) < 0) {
            log_error("An error has occurred during file sending.");
            return -1;
        }
        memset(buffer, 0, BUF_SIZE * sizeof(char));
    }
    sendMessage(socket, FILE_DONE);
    return 0;
}

void sendFileSize(const int sockfd, FILE* filePtr){
    long size = getFileSize(filePtr);
    long converted = htonl(size);
    char message[8];
    memcpy(message, &converted, 8);
    sendMessage(sockfd, message);
}

void sendDirectory(const int sockfd, const struct File_d** dirTable){
    sendMessage(sockfd, DIR_START);
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    for(int i = 0; dirTable[i] != NULL; i++) {
        sprintf(buffer, "%d: %s\n", dirTable[i]->id, dirTable[i]->name);
        sendMessage(sockfd, buffer);
    }
    sendMessage(sockfd, DIR_DONE "\n");
}