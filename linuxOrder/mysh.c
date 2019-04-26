#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>

#define MAXARGC		20
#define MAXARGLEN	100

int main()
{
	char	*arg_list[MAXARGC];
	char	argbuf[MAXARGLEN];
	int	arg_cnt = 0;
	int	pid;
	int 	status;

	while(arg_cnt < MAXARGC){
		printf("ARGV[%d]?", arg_cnt);
		if( fgets(argbuf, MAXARGLEN, stdin) && *argbuf != '\n' ){
			argbuf[strlen(argbuf) - 1] = '\0';	//the last char is \n, modified to \0;
			char *str_p = malloc(strlen(argbuf) + 1);
			if(str_p == NULL){
				fprintf(stderr, "malloc failed\n");
				exit(1);
			}
			strncpy(str_p, argbuf, strlen(argbuf) + 1);
			arg_list[arg_cnt++] = str_p;
		}
		else{
			if(arg_cnt > 0){
				if( ( pid = fork() ) == -1)
					perror("fork failed");
				else if(pid == 0){
					execvp(arg_list[0], arg_list);
					perror("execvp failed");
					exit(1);
				}
				else{
					if(wait(&status) != pid){
						fprintf(stderr,"wait error\n");
						exit(1);
					}
					/*
					for(int i = 0; i < arg_cnt; ++ i)
						if(arg_list[arg_cnt] != NULL)
							free( arg_list[arg_cnt] );
					*/
				}
				arg_cnt = 0;
			}
		}
			
	}
	return 0;
}
