#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<utmp.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>


int logout_tty(char *line)
{
	int 		fd;
	struct utmp	rec;
	int 		len = sizeof(struct utmp);
	int 		retval = -1;

	if( (fd=open(UTMP_FILE, O_RDWR)) == -1 )
		return retval;
	while( len == read(fd, &rec, len) )
	{
		if( strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0 )
		{
			rec.ut_type = DEAD_PROCESS;
			if( time((long *)&rec.ut_time) != -1 )
				if( lseek(fd, -1 * len, SEEK_CUR) != -1)
					if( write(fd, &rec, len) != -1)
						retval = 0;
			break;
		}
	}

	if( close(fd) == -1 ) 
		retval = -1;
	return retval;
}

int main()
{
	return 0;
}
