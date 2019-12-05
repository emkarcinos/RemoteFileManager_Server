#pragma once

#include <netinet/in.h>
#include <connector.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "applet.h"
#include "log.h"
#include "io.h"

void serveConnections(const int sockfd, const int flag) {
    struct sockaddr_in endpointAddr;
    int nextsock = getTcpEndpoint(sockfd, &endpointAddr);
    if (flag == 1) {
        log_info("Serving connections in parallel");
        pid_t child_pid = fork();
        if (child_pid > 0) {
            log_info("Created child process (PID: %d) for a connection with %s.", child_pid,
                     inet_ntoa(endpointAddr.sin_addr));
        } else if (child_pid == 0) {/* child process */
            appLoop(nextsock);
        } else
            log_error("An attempt to create child process has failed.");
    } else {
        log_info("Serving a single connection");
        appLoop(nextsock);
    }
}

void appLoop(const int sockfd){
    sendString(sockfd, "Welcome to the file server. We're here to serve you.");
    struct File_d** directory = getDirectory("/home/marcin/Downloads");
    sendString(sockfd, "Choose a file from the list to download:");
    sendDirectory(sockfd, (const struct File_d **) directory);
    sendString(sockfd, "Type a file number you wish to download:");
    askForInput(sockfd);
    int ans = readInt(sockfd);
    FILE* fp = getFilePtrFromDir((const struct File_d **) directory, ans);
    char* fileName = getFileNameFromDir((const struct File_d **) directory, ans);
    char *message = malloc(sizeof(char)*BUF_SIZE);
    sprintf(message, "Selected file: %s", fileName);
    sendString(sockfd, message);
    free(message);
    sendFileSize(sockfd, fp);
    sendString(sockfd, "Do you want to download this file? [Y/n]");
    askForInput(sockfd);
    ans = readInt(sockfd);
    if(ans == 1) {
        sendString(sockfd, fileName);
        sendFile(fp, sockfd);
    } else
        sendEndOfService(sockfd);
    sendString(sockfd, "That's all that we can offer right now. Goodbye.");
    sendEndOfService(sockfd);
}
