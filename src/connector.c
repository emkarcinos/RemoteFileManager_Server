#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"
#include "connector.h"


int getTcpEndpoint(const int sock, struct sockaddr_in *endpointAddr) {
    int endpoint;
    socklen_t len = sizeof(struct sockaddr_in);
    log_info("Waiting for connection...");
    endpoint = accept(sock, (struct sockaddr *) endpointAddr, &len);
    if (endpoint < 0) {
        log_error("Connection failed.");
        return -1;
    } else {
        log_info("Connection from: %s", inet_ntoa(endpointAddr->sin_addr));
    }
    return endpoint;
}
