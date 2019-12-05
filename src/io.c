#pragma once

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "io.h"
#include "log.h"
#include "protocol.h"
#include "htonll.h"

int readInt(const int socket) {
    char msg[4];
    memset(msg, 0, 4);
    log_info("Waiting for message...");
    if (recv(socket, msg, 4, 0) <= 0) {
        log_warn("Received an empty message");
        return -1;
    }
    log_info("Message: %s", msg);
    int result = (msg[3] << 24 | msg[2] << 16 | msg[1] << 8 | msg[0]);
    return result;
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
    unsigned int converted = htonl(len);
    memcpy(finalMessage+1, &converted, 4);
    /* Remaining part of the packet is filled with data */
    memcpy(finalMessage+5, message, len);

    return finalMessage;
}

int getPacketSize(const char* packet){
    int lenEndian = 0;
    memcpy(&lenEndian, packet+1, 4);
    int result = ntohl(lenEndian);
    return result + 5;
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
        const int len = strlen(buffer);
        const char* packet = composePacket(T_DIR, len, buffer);
        sendPacket(sockfd, packet);
        sendPacket(sockfd, composePacket(DONEFOR, 1, "0"));
    }
}

void sendFileSize(int sockfd, FILE* filePtr){
    long size = getFileSize(filePtr);
    long sizeEndian = htonll(size);
    char buffer[8];
    memcpy(buffer, &sizeEndian, 8);
    const char* packet = composePacket(T_LL, sizeof(long), buffer);
    sendPacket(sockfd, packet);
}

void sendEndOfService(int sockfd){
    sendPacket(sockfd, composePacket(DONEFOR, 1, "0"));
}

void askForInput(int sockfd){
    sendPacket(sockfd, composePacket(USRIN, 1, "0"));
}