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

char **splitMessage(const char *message, const int segmentSize) {
    return NULL;
}