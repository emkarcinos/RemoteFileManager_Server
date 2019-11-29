#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "tcp_sock.h"
#include "connector.h"
#include "stdio.h"
#include "log.h"

int main(int argc, char* argv[]){
    int sockfd = bindSocket(9999);
    int running = 1;
    unsigned int p_count = 0;
    while(running){
        struct sockaddr_in *endpointAddr;
        int nextsock = getTcpEndpoint(sockfd, endpointAddr);
        if(p_count <= MAX_CONNECTIONS){
            pid_t child_pid = fork();
            if(child_pid > 0) {
                p_count++;
                log_info("Created child process (PID: %d) for connection with %s. \n"
                       "Current child processes count: %d", child_pid, inet_ntoa(endpointAddr->sin_addr), p_count);
            } else if (child_pid == 0){ /* child process */
                //TODO
            } else
                log_error("An attempt to create child process has failed.");
        } else {
            log_warn("Child process count exceeded the limit of %d", MAX_CONNECTIONS);
            log_info("Waiting for a child process to finish...");
        }
    }
    printf("ASD\n");
    return 0;
}