#pragma once

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "io.h"
#include "log.h"
#include "protocol.h"

/* deprecated */
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

/* deprecated */
int sendMessage(int socket, const char *message) {
    char* temp = getMessage(socket);
    if(strcmp(temp, C_ACK)==0){
        log_info("Sending a message...");
        int receivedBytes = send(socket, message, BUF_SIZE, 0);
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
    }]
    return 0;
}

/* deprecated */
void sendFileSize(const int sockfd, FILE* filePtr){
    long size = getFileSize(filePtr);
    long converted = size;
    char message[8];
    memcpy(message, &converted, 8);
    sendMessage(sockfd, message);
}

char* composePacket(const char type, const int len, const char* message){
    if (len > BUF_SIZE - 5){
        log_error("The packet's size is too large.");
        return NULL;
    }
    char* finalMessage = malloc(sizeof(char)*BUF_SIZE);
    memset(finalMessage, 0, len + 5);
    /* First byte is a char */
    memcpy(finalMessage, &type, 1);
    /* Next 4 bytes are an integer indicating the length */
    int converted = htonl(len);
    memcpy(finalMessage+1, &converted, 4);
    /* Remaining part of the packet is filled with data */
    memcpy(finalMessage+5, message, len);

    return finalMessage;
}

int getPacketSize(const char* packet){
    int lenEndian = 0;
    memcpy(lenEndian, packet+1, 4);
    int result = ntohl(lenEndian);
    return result;
}

void sendPacket(int sockfd, const char* packet){
    int len = getPacketSize(packet);
    log_info("Sending a packet of length %d.", len);
    int sentBytes = send(sockfd, packet, len, 0);
    if (sentBytes <= 0)
        log_error("An error has occurred during sending.");
    else
        log_info("Packet sent.");
}

void sendString(int sockfd, const char* message){
    const int len = strlen(message);
    const char* packet = composePacket(T_STR, len, message);
    sendPacket(sockfd, packet);
}

void sendDirectory(const int sockfd, const struct File_d** dirTable){
    char buffer[BUF_SIZE];
    for(int i = 0; dirTable[i] != NULL; i++) {
        memset(buffer, 0, BUF_SIZE);
        sprintf(buffer, "%d: %s", dirTable[i]->id, dirTable[i]->name);
        sendString(sockfd, buffer);
    }
}
