#pragma once

#include <netinet/in.h>
#include <connector.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "applet.h"
#include "log.h"
#include "io.h"
#include "protocol.h"

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
            appLoop(sockfd);
        } else
            log_error("An attempt to create child process has failed.");
    } else {
        log_info("Serving a single connection");
        char *message = getMessage(nextsock);
        printf("%s\n", message);
    }
}

void appLoop(const int sockfd){
    /* Welcome message */
    sendMessage(sockfd, "Welcome to the file server. We're here to serve you.");
    struct File_d** directory = getDirectory("/home/marcin/Downloads");
    int running = 1;
    while(running){
        sendMessage(sockfd, "Choose a file from the list to download:");
        sendDirectory(sockfd, (const struct File_d **) directory);
        char* response = getMessage(sockfd);
        if (response == C_STOP){
            sendMessage(sockfd, "Goodbye.");
            running = 0;
        } else if (response == C_FILE){
            char* msg = getMessage(sockfd);
            FILE* filePtr=getFilePtrFromDir((const struct File_d **) directory, atoi(msg));
            sendFileSize(sockfd, filePtr);
            response = getMessage(sockfd);
            if(response == C_NO)
                continue;
            else if (response == C_YES)
                sendFile(filePtr, sockfd);
        } else if (response == C_DIR) {
            sendDirectory(sockfd, (const struct File_d **) directory);
        }
    }
    exit(0);
}
