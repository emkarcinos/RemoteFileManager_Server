#include "tcp_sock.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
struct sockaddr_in socketAddr;

int bindSocket(const int port) {
    log_info("Starting server on port %d");
    log_info("Creating socket...");
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd > 0)
        log_info("Socket created successfully.");
    else {
        log_error("An error has occurred during socket creation. Exiting.");
        exit(EXIT_FAILURE);
    }
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(port);
    socketAddr.sin_addr.s_addr = INADDR_ANY;

    log_info("Binding...");
    if (bind(sockfd, (struct sockaddr *) &socketAddr,
             sizeof(struct sockaddr_in)) < 0) {
        log_error("An error has occurred during binding the socket. Exiting.");
        exit(EXIT_FAILURE);
    }
    log_info("Binding successful.");

    log_info("Listening on port %d...", port);
    listen(sockfd, MAX_CONNECTIONS);
    return sockfd;
}
