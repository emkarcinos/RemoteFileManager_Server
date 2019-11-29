#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "tcp_sock.h"
#include "connector.h"
#include "stdio.h"
#include "log.h"

int main(int argc, char *argv[]) {
    int sockfd = bindSocket(9999);
    int running = 1;
    while (running) {
        struct sockaddr_in *endpointAddr;
        int nextsock = getTcpEndpoint(sockfd, endpointAddr);
        pid_t child_pid = fork();
        if (child_pid > 0) {
            log_info("Created child process (PID: %d) for a connection with %s.", child_pid,
                     inet_ntoa(endpointAddr->sin_addr));
        } else if (child_pid == 0) {/* child process */
            int x = 5;
        } else
            log_error("An attempt to create child process has failed.");
    }
    printf("ASD\n");
    return 0;
}