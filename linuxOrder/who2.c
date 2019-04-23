#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define UTMPBUFSIZE	16
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

int readInBuf(int utmpfd, struct utmp *buf, int buflen)
{
	int ret, i;
	int utmplen = sizeof(struct utmp);
	for(i = 0 ;i < buflen; ++ i)
	{
		ret = read(utmpfd, buf + i, utmplen);
		if( ret != utmplen )
			break;
	}
	return i + 1;
}

int main(int argc, char** argv)
{
	struct utmp	buf[UTMPBUFSIZE];
	int bufsize = UTMPBUFSIZE;
	int utmpfd;
	if( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while( bufsize == UTMPBUFSIZE )
	{
		bufsize = readInBuf(utmpfd, buf, bufsize);
		for(int i = 0; i < bufsize; ++ i)
			show_info(buf+i);
	}
	return 0;

}
