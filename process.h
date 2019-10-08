#ifndef PROCESS_H
#define PROCESS_H


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"file.h"

typedef struct {
        char ***commands;
        int **args;
	char **result;
	char* interresult;
        int len;
	int size;
	int interresultlen;
	int execcount;
} process_datas;

int process_pipe(char** commands, int fd[2], pid_t *son);
int process_popen(process_datas * p);
int process_finished(pid_t pid);
int process_datas_internal(process_datas *p, int *i);
int process_append_cmd(char * param, process_datas * datas, int new_command);
int process_exec(process_datas *p);
int process_datas_destroy(process_datas *p);
int process_datas_init(process_datas *p);

#endif
