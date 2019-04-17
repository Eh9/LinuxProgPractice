#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>

#define SHOWHOST 		//??

void show_info(struct utmp* utp)
{
	printf("%-8.8s ", utp->ut_user);
	printf("%-8.8s ", utp->ut_line);
	printf("%-8.8s ", utp->ut_id);
	printf("%10ld", utp->ut_tv.tv_sec);
#ifdef SHOWHOST
	printf("%-8.8s ", utp->ut_host);
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

		/*	{
		printf("%s", current_record.ut_line);
		printf("\t%s", current_record.ut_id);
		printf("\t%s", current_record.ut_user);
		printf("\t%s", current_record.ut_host);
		printf("\t%d\n", current_record.ut_pid);
	}*/

	close(utmpfd);
	return 0;

}
