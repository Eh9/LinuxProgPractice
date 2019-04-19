#include<dirent.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>


void do_ls(char *pathname)
{
	DIR* 			dirp;
	struct dirent*		direntp;

	if( (dirp = opendir(pathname)) == NULL )
		perror("open direct failed!");
	else{
		while( (direntp = readdir(dirp)) )
		{
			printf("%s  ",direntp->d_name);
		}
		printf("\n");
		closedir(dirp);
	}
}

int main(int argc, char ** argv)
{
	if(argc == 1)
		do_ls(".");
	else
		while(-- argc){
			printf("%s", *++argv);
			do_ls(*argv);
		}
	return 0;
}
