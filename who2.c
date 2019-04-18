#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST 		

void show_info(struct utmp* utp)
{
	if(utp->ut_type != USER_PROCESS)
		return;
	char timebuf[40];
	size_t timesize = strftime(timebuf, 40, "%g-%m-%d %H:%M", localtime((long *)&utp->ut_time));
	printf("%-8.8s ", utp->ut_user);
	printf("%-8.8s ", utp->ut_line);
	printf("%-4.8s ", utp->ut_id);
	if(timesize == 0)	
		printf("buf lenth too short\n");
	else	
		printf("%-8.20s ", timebuf);
#ifdef SHOWHOST
	printf("(%s)", utp->ut_host);
#endif
	printf("\n");
}

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
		show_info(&current_record);
	close(utmpfd);
	return 0;

}
