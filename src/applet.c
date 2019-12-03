#pragma once

#include <netinet/in.h>
#include <connector.h>
#include <unistd.h>
#include <arpa/inet.h>
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
            //TODO
        } else
            log_error("An attempt to create child process has failed.");
    } else {
        log_info("Serving a single connection");
        char *message = getMessage(nextsock);
        printf("%s\n", message);
    }
}
