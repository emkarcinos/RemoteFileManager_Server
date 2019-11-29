#pragma once

#define MAX_CONNECTIONS 5

extern struct sockaddr_in socketAddr;

int bindSocket(int port);
