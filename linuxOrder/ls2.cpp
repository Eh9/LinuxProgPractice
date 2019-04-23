#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

#define SHOWALLFILE	1
#define	SHOWLIST	2

using namespace std;

void do_ls(char *pathname, int lsMode)
{
	DIR* 			dirp;
	struct dirent*		direntp;
	vector<dirent*>		dirVec;

	if( (dirp = opendir(pathname)) == NULL )
		perror("open direct failed!");
	else{
		if(lsMode & SHOWALLFILE)
			while( (direntp = readdir(dirp)) )
				dirVec.push_back(direntp);
		else{
			while( (direntp = readdir(dirp)) )
				if(direntp->d_name[0] != '.')
					dirVec.push_back(direntp);
		}
		sort(dirVec.begin(), dirVec.end(), 
				[](dirent* p1, dirent* p2){
				return strncmp(p1->d_name, p2->d_name, 256) < 0;});
		for(const auto &i: dirVec){
			if(lsMode & SHOWLIST){
			//todo
				;
			}
			else
				printf("%s  ", i->d_name);
		}
		printf("\n");
		closedir(dirp);
	}
}

int main(int argc, char ** argv)
{
	int lsMode = 0;
	bool noPath = true;
	for(int i = 1; i < argc; ++i){
		if( *(argv + i)[0] == '-')
			for(int j = 1; argv[i][j] != 0; ++ j){
				if( (*(argv+i))[j] == 'a')
					lsMode |= SHOWALLFILE;
				else if( argv[i][j] == 'l')
					lsMode |= SHOWLIST;
				else{
					printf("%c: no such option!\n", argv[i][j]);
					exit(1);
				}
			}
	}
	for(int i = 1; i < argc; ++ i){
		if( *(argv + i)[0] != '-'){
			noPath = false;
//			printf("%s:\n", *(argv+i));
			do_ls(*(argv+i), lsMode);
		}
	}
	if(noPath){
//		printf(".:\n");
		char temp[] = ".";
		do_ls(temp, lsMode);
	}
	return 0;
}
