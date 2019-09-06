#define _GNU_SOURCE
#include"process.h"
#include"file.h"

extern char **environ;

int process_pipe(char** commands, int fd[2], pid_t *son)
{
	
	int	tube_1[2];
        int	tube_2[2];
        if ((pipe(tube_1) != 0) || (pipe(tube_2) != 0))
                return EXIT_FAILURE;

        switch(*son = fork())
        {
                case -1:
			close(tube_1[0]); close(tube_1[1]);
                        close(tube_2[0]); close(tube_2[1]);
                        perror("fail to fork in process_pipe");
			return errno;
                break;
                case 0: ;
                        setpgid(0, 0);
                        close(tube_1[1]);
                        close(tube_2[0]);
			dup2(tube_1[0], STDIN_FILENO);
                        dup2(tube_2[1], STDOUT_FILENO);
                        execve(commands[0], commands, environ);
                       	perror("execve in process_pipe");
                       	return errno;
                break;
                default: ;
                         setpgid(*son, *son);
                        close(tube_1[0]);
                        close(tube_2[1]);
                        fd[0] = tube_2[0];
                        fd[1] = tube_1[1];
        }
	return EXIT_SUCCESS;
}

int process_popen(char ** result, char** commands, int args, int *size)
{
        FILE* fd;
	int len = 0;
	for(int i = 0; i < args - 1; i++)
	{
		len += strlen(commands[i]) + 2;
	}
        char *command = calloc(len, sizeof(char));
	char *c = command;
	for(int i = 0; i < args - 1; i++)
	{
		sprintf(command, "%s ", commands[i]);
		command += strlen(commands[i]) + 1;
	}
        if((fd = popen(c, "r")) != NULL)
        {
		if(file_fgetsn(result, fd, size))
		{
			free(command - strlen(c));
			pclose(fd);
			perror("fgetsn in process_popen");
			return EXIT_FAILURE;
		}
        }else{
		free(command - strlen(c));
                perror("popen in process_popen");
                return EXIT_FAILURE;
        }
	free(command - strlen(c));
        pclose(fd);
        return EXIT_SUCCESS;
}
int process_append_cmd(char *param, process_datas *datas, int new_command)
{
	if(!new_command)
	{
		if(datas->size)
		{
			int args = datas->args[datas->size - 1][1]++;
			if(args > datas->args[datas->size - 1][0])
			{
				datas->args[datas->size - 1][0] += 1;
				datas->commands[datas->size - 1] = (char**)realloc(datas->commands[datas->size - 1],
				datas->args[datas->size - 1][0] * sizeof(char*));
			}
			datas->commands[datas->size - 1][datas->args[datas->size - 1][1] - 1] = (char*) NULL;
		}
		datas->size++;
		if(!datas->len)
		{
			datas->len = datas->size;
			datas->args = (int **) calloc(datas->len, sizeof(int*));
			datas->args[0] = (int*) calloc(2, sizeof(int));
			datas->args[0][0] = 7;
			datas->args[0][1] = 1;
			datas->commands = (char***) calloc(datas->len, sizeof(char**));
			datas->commands[0] = (char**) calloc(7, sizeof(char*));
		}else
		if(datas->size > datas->len)
		{
			datas->len = datas->size;
			datas->args = (int **)realloc(datas->args, datas->len * sizeof(int*));
			datas->args[datas->size - 1] = (int *)calloc(2, sizeof(int));
			datas->args[datas->size - 1][0] = 7;
			datas->args[datas->size - 1][1] = 1;
			datas->commands = (char***) realloc(datas->commands, datas->len * sizeof(char**));
			datas->commands[datas->size - 1] = (char **) calloc(7, sizeof(char*));
		}
	}else{
		int args = datas->args[datas->size - 1][1]++;
		if(!(args - datas->args[datas->size - 1][0]))
		{
			datas->args[datas->size - 1][0] += 7;
			datas->commands[datas->size - 1] = (char**) realloc(datas->commands[datas->size - 1], 
					datas->args[datas->size - 1][0] * sizeof(char*));
		}
	}
	datas->commands[datas->size - 1][datas->args[datas->size - 1][1] - 1] = strdup((char *)param);

	return EXIT_SUCCESS;
}

int process_finished(pid_t pid)
{
        errno = 0;
        int status;
        while(1)
        {
                usleep(2000);
                pid_t check;
                if((check = waitpid(pid, &status, WNOHANG|WUNTRACED)) > 0)
                {
                        if(WIFEXITED(status))
                        {
                                printf("%ld terminated successfully : %s\n", (long) pid, "signal OK !");
                                return EXIT_SUCCESS;
                        }else if(WIFSIGNALED(status))
                        {
                                printf("%ld terminated by signal : %s\n", (long) pid, strsignal(WTERMSIG(status)));
                        }else if(WIFSTOPPED(status))
                        {
                                printf("%ld stopped by signal : %s\n", (long) pid, strsignal(WSTOPSIG(status)));
                        }else if(WIFCONTINUED(status))
                        {
                                printf("%ld continued\n", (long) pid);
                        }
                }else if(check == -1){
                        return errno;
                }
        }
        return EXIT_FAILURE;
}

int process_exec(process_datas *p)
{
	int ret = 0, k = 0;
	char * result = NULL;
	int size= 0;
	int args = p->args[p->size - 1][1]++;
	if(args > p->args[p->size - 1][0])
	{
	    p->args[p->size - 1][0] += 1;
	    p->commands[p->size - 1] =
		    realloc(p->commands[p->size - 1],
			    p->args[p->size - 1][0] * sizeof(char*));
	}
	p->commands[p->size - 1][p->args[p->size - 1][1] - 1] = (char*) NULL;
	p->execcount++;
	p->result = realloc(p->result, p->execcount * sizeof(char*));

	if((ret = process_datas_internal(p, &result, &size, &k)) == EXIT_FAILURE)
	{
		free(result);
		perror("Error in first command in process_exec: not / or bad internal process");
		return EXIT_FAILURE;
	}else if(ret == 254 || ret == 255 || ret == EXIT_SUCCESS){
		if((ret = process_popen(&result, p->commands[0], p->args[0][1], &size)) == EXIT_FAILURE)
		{
			if(result != NULL)
				free(result);
			perror("Error in first command in process_exec from process_popen\n");
			return EXIT_FAILURE;
		}
	}
	if(p->size == 1)
	{
		p->result[p->execcount - 1] = strdup(result);
		free(result);
		process_datas_init(p);
		return EXIT_SUCCESS;
	}
        int tube[2];
	pid_t son;
	int error;
        for(int i = 1; i < p->size; i++)
        {
		if((ret = process_datas_internal(p, &result, &size, &i)) == EXIT_FAILURE)
		{
			free(result);
			perror("Bad internal process");
			return EXIT_FAILURE;
		}else if(i == p->size)
			break;
		if((ret = process_pipe(p->commands[i], tube, &son))) {
			free(result);
			perror("fail to process_pipe in process_exec");
			return errno;
		}
		if(fd_writen(tube[1], result, strlen(result), 1))
		{
			free(result);
			perror("fail to write in fd in process_exec");
			return EXIT_FAILURE;
		}
		close(tube[1]);
		if((error = process_finished(son)) != EXIT_SUCCESS)
		{
			free(result);
			return error;
		}
		if(fd_readn(&result, tube[0], &size))
		{
			free(result);
			perror("fail to read from fd in process_exec");
			return EXIT_FAILURE;
		}
		close(tube[0]);
	}
	p->result[p->execcount - 1] = strdup(result);
	free(result);
	process_datas_init(p);
        
	return EXIT_SUCCESS;

}

int process_datas_internal(process_datas *p, char **result, int *size, int *i)
{
	if(!strcmp(p->commands[*i][0], "file"))
	{
		FILE *f = fopen(p->commands[*i][1], "w+");
		if (f == NULL)
		{
			free(*result);
			perror("Error opening file in process_exec\n");
			return EXIT_FAILURE;
		}

		fprintf(f, *result);

		fclose(f);
		++(*i);
		return 254;
	}else if(!strcmp(p->commands[*i][0], "cd")){
		chdir(p->commands[*i][1]);
		++(*i);
		return 255;
	}else if(!strcmp(p->commands[*i][0], "concat")){
		int len = 0;
		for(int l = 1; l < p->args[*i][1] - 1; l++)
			len += strlen(p->commands[*i][l]);
		if(*size < len){
			if(*result == NULL)
				*result = calloc(len +1,  sizeof(char));
			else
				*result = realloc(*result, (len + 1) * sizeof(char));
			*size = len;
		}
		strncpy(*result, p->commands[*i][1], strlen(p->commands[*i][1]));
		for(int l = 2; l < p->args[*i][1] - 1; l++)
		{
			strncat(*result, p->commands[*i][l], strlen(p->commands[*i][l]));
		}
		++(*i);
		return 256;
	}
	return EXIT_SUCCESS;
}

int process_datas_init(process_datas *p)
{
	for(int i = 0; i < p->size; i++)
	{
		for(int j = 0; j < p->args[i][1]; j++)
		{
			free(p->commands[i][j]);
			p->commands[i][j] = NULL;
		}
		p->args[i][1] = 1;
	}
	p->size = 0;
	
	return EXIT_SUCCESS;

}

int process_datas_destroy(process_datas *p)
{
	for(int i = 0; i < p->len; i++)
	{
		for(int j = 0; j < p->args[i][1]; j++)
		{
			if(p->commands[i][j] != NULL)
			{
				free(p->commands[i][j]);
				p->commands[i][j] = NULL;
			}
		}
		free(p->commands[i]);
		p->commands[i] = NULL;
	}
	free(p->commands);
	p->commands = NULL;

        for(int i = 0; i < p->len; i++)
        {
            free(p->args[i]);
		    p->args[i] = NULL;
        }
        free(p->args);
	p->args = NULL;
	p->len = 0;
	p->size = 0;
	for(int i = 0; i < p->execcount; i++)
	{
		free(p->result[i]);
		p->result[i] = NULL;
	}
	free(p->result);
	p->result = NULL;
	p->execcount = 0;
	return EXIT_SUCCESS;
}

