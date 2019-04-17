#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>

#define SHOWHOST 		//??


int main(int argc, char** argv)
{
	struct utmp	current_record;
	int 		utmpfd;
	int		reclen = sizeof(current_record);

	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(reclen == read(utmpfd, &current_record, reclen))
	{
		printf("%s", current_record.ut_line);
		printf("\t%s", current_record.ut_id);
		printf("\t%s", current_record.ut_user);
		printf("\t%s", current_record.ut_host);
		printf("\t%d\n", current_record.ut_pid);
	}
	close(utmpfd);
	return 0;

}
