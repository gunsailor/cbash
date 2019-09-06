#include"file.h"


int file_read(char **result, int *size)
{
        FILE * file = (void*) NULL;
	struct stat status;
	char * content = (void*) NULL;

        if (stat(*result, & status) != 0) {
		perror("stat");
		return EXIT_FAILURE;
	}
	if ((content = malloc(status.st_size)) == NULL) {
		perror("malloc");
		return EXIT_FAILURE;
	}
	if ((file = fopen(*result, "r")) == NULL) {
		free(content);
		perror("fopen");
		return EXIT_FAILURE;
	}
	if ((signed int)fread(content, 1, status.st_size, file) != status.st_size) {
		free(content);
		perror("fread");
		return EXIT_FAILURE;
	}

        *size = status.st_size;
        *result = content;
	fclose(file);
	return EXIT_SUCCESS;
}

int file_fgetsn(char **result, FILE* fd, int *size)
{
	int i = 0, j = 0;
	char buffer[64] = {'\0'};
	if(!(*size >= 128))
	{
		j = 128;
		*result = calloc(j, sizeof(char));
	}else{
		j = *size;
	}
	if(*result)
	{
		while(fgets(buffer, 64, fd) != NULL)
		{
			if(!i)
				strncpy(*result, buffer, strlen(buffer));
			else
				strncat(*result, buffer, strlen(buffer));
			i += strlen(buffer);
			if((j - i) < 64)
			{
				j = i + 128;
				*result = realloc(*result, j);
				if(*result == NULL)
				{
					perror("realloc in file_fgetsn");
					return EXIT_FAILURE;
				}
			}
		}
	}else{
		perror("malloc in file_fgetsn");
		return EXIT_FAILURE;
	}
	*size = j;

	return EXIT_SUCCESS;
}

int fd_writen(const int sd, const char * b, const size_t s, const int retry_on_interrupt)
{
	size_t n = s;
	while (0 < n)
	{
		ssize_t result = write(sd, b, n);
		if (-1 == result)
		{
			if ((retry_on_interrupt && (errno == EINTR)) || (errno == EWOULDBLOCK) || (errno == EAGAIN))
			{
				continue;
			}
			else
			{
				break;
			}
		}

		n -= result;
		b += result;
	}

	if(0 < n){
		perror("write in fd_writen");
		return EXIT_FAILURE;
	}else{	
		return EXIT_SUCCESS;
	}
}

int fd_readn(char** result, int fd, int *size)
{
	int m = 0; 
	char buffer[2] = {'\0'};
	while(read(fd, buffer, 1))
	{
		if(!m)
			strcpy(*result, buffer);
		else
			strcat(*result, buffer);
		m += strlen(buffer);
		if((*size - m) < 64)
		{
			*size = m + 128;
			*result = realloc(*result, *size);
		}
		if(*result == NULL)
		{
			perror("realloc in file_read");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
