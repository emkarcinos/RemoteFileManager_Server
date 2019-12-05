#pragma once

#include <unistd.h>

#include "tcp_sock.h"
#include "applet.h"

int main(int argc, char *argv[]) {
    int sockfd = bindSocket(9999);
    serveConnections(sockfd, 0);
    close(sockfd);
    return 0;
}