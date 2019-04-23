#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

#define BUFFERSIZE	4096
#define COPYMODE	0644

void oops(char *, char *);

int main(int argc, char** argv)
{
	int	in_fd, out_fd, n_chars;
	char	buf[BUFFERSIZE];

	if(argc != 3)
	{
		fprintf(stderr, "%s arguments counts fault!\n", argv[0]);
		exit(1);
	}

	if( (in_fd = open(argv[1], O_RDONLY)) == -1 )
		fprintf(stderr, "%s file open failed!\n", argv[1]);
	if( (out_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, COPYMODE)) == -1 )
		fprintf(stderr, "%s file creat failed!\n", argv[2]);

	while( n_chars = read(in_fd, buf, BUFFERSIZE) )
		if(n_chars != write(out_fd, buf, n_chars))	
			fprintf(stderr, "%s file write error!\n", argv[2]);

	if(n_chars == -1)
		fprintf(stderr, "%s file read error!\n", argv[1]);

	if(close(in_fd) == -1 || close(out_fd) == -1)
		fprintf(stderr, "file close failed!\n");

	return 0;
}
