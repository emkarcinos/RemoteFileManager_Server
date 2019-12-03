#pragma once

#include "tcp_sock.h"
#include "applet.h"

int main(int argc, char *argv[]) {
    int sockfd = bindSocket(9999);
    int running = 1;
    while (running) {
        serveConnections(sockfd, 0);
    }
    return 0;
}