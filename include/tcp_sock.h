#pragma once

#define MAX_CONNECTIONS 5

extern struct sockaddr_in socketAddr;
extern int sockfd;

int bindSocket(int port);
