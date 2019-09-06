#ifndef FILE_H
#define FILE_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>

int file_read(char **result, int *size);
int file_fgetsn(char **result, FILE* fd, int *size);
int fd_writen(const int sd, const char * b, const size_t s, const int retry_on_interrupt);
int fd_readn(char** result, int fd, int *size);

#endif
