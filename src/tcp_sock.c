#pragma once

#include "tcp_sock.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int bindSocket(int port) {
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(port);
    socketAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &socketAddr,
             sizeof(struct sockaddr_in)) < 0) {
        printf("Bind has failed.\n");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, MAX_CONNECTIONS);
    return sockfd;
}
