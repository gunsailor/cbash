#define _DEFAULT_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"process.h"

int main(int argc, char **argv)
{
	int ret;
	process_datas p = {NULL, NULL, NULL, 0, 0, 0};
	char *cwd = calloc(1,256);
	getcwd(cwd, 256);
	process_append_cmd("/usr/bin/wget", &p, 0);
	process_append_cmd(argv[1], &p, 1);
	process_append_cmd("-O-", &p, 1);

	if(!(ret = process_exec(&p)))
	{
      		process_append_cmd("concat", &p, 0);
      		process_append_cmd("\"", &p, 1);
      		process_append_cmd(p.result[0], &p, 1);
      		process_append_cmd("\"", &p, 1);
		process_append_cmd("/usr/bin/pup", &p, 0);
		process_append_cmd("--charset", &p, 1);
		process_append_cmd("utf-8", &p, 1);
		process_append_cmd("div h1.pl-header-title text{}", &p, 1);
		process_append_cmd("/usr/bin/awk", &p, 0);
		process_append_cmd("1", &p, 1);
		process_append_cmd("ORS=", &p, 1);
	
		if(!(ret = process_exec(&p)))
		{
			process_append_cmd("concat", &p, 0);
			process_append_cmd("\"", &p, 1);
			process_append_cmd(cwd, &p, 1);
			process_append_cmd("/", &p, 1);
			process_append_cmd(p.result[1], &p, 1);
			process_append_cmd("\"", &p, 1);

			if(!(ret = process_exec(&p)))
			{
				printf("%s\n", p.result[2]);
				process_append_cmd("/bin/mkdir", &p, 0);
				process_append_cmd(p.result[2], &p, 1);
				process_append_cmd("cd", &p, 0);
				process_append_cmd(p.result[1], &p, 1);
				
				if(!(ret = process_exec(&p)))
				{
					process_append_cmd("concat", &p, 0);
					process_append_cmd("\"", &p, 1);
					process_append_cmd(p.result[0], &p, 1);
					process_append_cmd("\"", &p, 1);
					process_append_cmd("/usr/bin/pup", &p, 0);
					process_append_cmd("--charset", &p, 1);
					process_append_cmd("utf-8", &p, 1);
					process_append_cmd("div#content a attr{href}", &p, 1);
					process_append_cmd("/bin/grep", &p, 0);
					process_append_cmd("watch", &p, 1);
					process_append_cmd("/usr/bin/cut", &p, 0);
					process_append_cmd("-d;", &p, 1);
					process_append_cmd("-f1", &p, 1);
					process_append_cmd("/usr/bin/cut", &p, 0);
					process_append_cmd("-d&", &p, 1);
					process_append_cmd("-f1", &p, 1);
					process_append_cmd("/usr/bin/uniq", &p, 0);
					process_append_cmd("/bin/sed", &p, 0);
					process_append_cmd("-es;\\(^[/]\\);https://www.youtube.com\\1;g", &p, 1);
					process_append_cmd("/usr/bin/xargs", &p, 0);
					process_append_cmd("-n1", &p, 1);
					process_append_cmd("/usr/local/bin/youtube-dl", &p, 1);
					process_append_cmd("--user-agent=Mozilla", &p, 1);
					process_append_cmd("--extract-audio", &p, 1);
					process_append_cmd("--audio-format", &p, 1);
					process_append_cmd("mp3", &p, 1);
					process_append_cmd("--audio-quality", &p, 1);
					process_append_cmd("0", &p, 1);
					process_append_cmd("/usr/bin/find", &p, 0);
					process_append_cmd("-iname", &p, 1);
					process_append_cmd("*'*", &p, 1);
					process_append_cmd("-exec", &p, 1);
					process_append_cmd("/usr/bin/rename", &p, 1);
					process_append_cmd("s/'/ /g", &p, 1);
					process_append_cmd("{}", &p, 1);
					process_append_cmd("\;", &p, 1);

					if(!(ret = process_exec(&p)))
					{
						process_append_cmd("/bin/ls", &p, 0);
						process_append_cmd("file", &p, 0);
						process_append_cmd(argv[2], &p, 1);
						process_append_cmd("/bin/sed", &p, 0);
						process_append_cmd("-i", &p, 1);
						process_append_cmd("-es;\\(.*\\)-[^ ]*.mp3;\\1;g", &p, 1);
						process_append_cmd(argv[2], &p, 1);
						process_append_cmd("/bin/cat", &p, 0);
						process_append_cmd(argv[2], &p, 1);
						process_append_cmd("/usr/bin/xargs", &p, 0);
						process_append_cmd("-n1", &p, 1);
						process_append_cmd("-I[]", &p, 1);
						process_append_cmd("/usr/bin/find", &p, 1);
						process_append_cmd("-name", &p, 1);
						process_append_cmd("*[]*", &p, 1);
						process_append_cmd("-exec", &p, 1);
						process_append_cmd("/bin/mv", &p, 1);
						process_append_cmd("{}", &p, 1);
						process_append_cmd("[].mp3", &p, 1);
						process_append_cmd("\;", &p, 1);
						process_append_cmd("/bin/rm", &p, 0);
						process_append_cmd(argv[2], &p, 1);

						if(!(ret = process_exec(&p)))
						{
							process_append_cmd("concat", &p, 0);
							process_append_cmd("artist=", &p, 1);
							process_append_cmd(argv[2], &p, 1);

							if(!(ret = process_exec(&p)))
							{
								process_append_cmd("concat", &p, 0);
								process_append_cmd("album=", &p, 1);
								process_append_cmd(p.result[1], &p, 1);

								if(!(ret = process_exec(&p)))
								{
									process_append_cmd("/bin/ls", &p, 0);
									process_append_cmd("/usr/bin/cut", &p, 0);
									process_append_cmd("-d.", &p, 1);
									process_append_cmd("-f1", &p, 1);
									process_append_cmd("/usr/bin/xargs", &p, 0);
									process_append_cmd("-n1", &p, 1);
									process_append_cmd("-I{}", &p, 1);
									process_append_cmd("/usr/bin/ffmpeg", &p, 1);
									process_append_cmd("-i", &p, 1);
									process_append_cmd("{}.mp3", &p, 1);
									process_append_cmd("-metadata", &p, 1);
									process_append_cmd(p.result[6], &p, 1);
									process_append_cmd("-metadata", &p, 1);
									process_append_cmd(p.result[7], &p, 1);
									process_append_cmd("-metadata", &p, 1);
									process_append_cmd("title={}", &p, 1);
									process_append_cmd("-ab", &p, 1);
									process_append_cmd("256k", &p, 1);
									process_append_cmd("{}.true.mp3", &p, 1);
									process_append_cmd("/bin/ls", &p, 0);
									process_append_cmd("/bin/grep", &p, 0);
									process_append_cmd("-v", &p, 1);
									process_append_cmd("true", &p, 1);
									process_append_cmd("/usr/bin/xargs", &p, 0);
									process_append_cmd("-n1", &p, 1);
									process_append_cmd("-I{}", &p, 1);
									process_append_cmd("/bin/rm", &p, 1);
									process_append_cmd("{}", &p, 1);

									if(!(ret = process_exec(&p)))
									{
										printf("downloaded !\n");
									}else{
										free(cwd);
										process_datas_destroy(&p);
										fprintf(stderr, "failed 9: %s \n", strerror(ret));
										fflush(stderr);
										exit(EXIT_FAILURE);
									}
								}else{
									free(cwd);
									process_datas_destroy(&p);
									fprintf(stderr, "failed 8: %s \n", strerror(ret));
									fflush(stderr);
									exit(EXIT_FAILURE);
								}
      				        		}else{
      				        			free(cwd);
      				        			process_datas_destroy(&p);
      				        			fprintf(stderr, "failed 7: %s \n", strerror(ret));
      				        			fflush(stderr);
      				        			exit(EXIT_FAILURE);
      				        		}
						}else{
							free(cwd);
							process_datas_destroy(&p);
							fprintf(stderr, "failed 6: %s \n", strerror(ret));
							fflush(stderr);
							exit(EXIT_FAILURE);
						}
					}else{
						free(cwd);
						process_datas_destroy(&p);
						fprintf(stderr, "failed 5: %s \n", strerror(ret));
						fflush(stderr);
						exit(EXIT_FAILURE);
					}
				}else{
					free(cwd);
					process_datas_destroy(&p);
					fprintf(stderr, "failed 4: %s \n", strerror(ret));
					fflush(stderr);
					exit(EXIT_FAILURE);
				}
			}else{
				free(cwd);
				process_datas_destroy(&p);
				fprintf(stderr, "failed 3: %s \n", strerror(ret));
				fflush(stderr);
				exit(EXIT_FAILURE);
			}
		}else{
			free(cwd);
			process_datas_destroy(&p);
			fprintf(stderr, "failed 2: %s \n", strerror(ret));
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
	}else{
		free(cwd);
		process_datas_destroy(&p);
		fprintf(stderr, "failed 1: %s \n", strerror(ret));
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	
	process_datas_destroy(&p);
	free(cwd);
	return EXIT_SUCCESS;
}
