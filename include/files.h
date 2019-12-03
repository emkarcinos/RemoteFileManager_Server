#pragma once

char** getDirectory(const char* path);

void sendDirectory(int sockfd, const char** dirTable);