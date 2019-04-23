#include<dirent.h>
#include<cstdlib>
#include<sys/stat.h>
#include<sys/types.h>
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include<vector>
#include<algorithm>


using namespace std;

void do_ls(char *pathname)
{
	DIR* 			dirp;
	struct dirent*		direntp;
	vector<dirent*>		dirVec;

	if( (dirp = opendir(pathname)) == NULL )
		perror("open direct failed!");
	else{
		while( (direntp = readdir(dirp)) )
			dirVec.push_back(direntp);
		sort(dirVec.begin(), dirVec.end(), 
				[](dirent* p1, dirent* p2)
				{return strcmp(p1->d_name, p2->d_name) < 0;});
		for(const auto &i: dirVec)
			printf("%s  ", i->d_name);
		printf("\n");
		closedir(dirp);
	}
}

int main(int argc, char ** argv)
{
	if(argc == 1)
	{	char temp[] = ".";
		do_ls(temp);
	}
	else
		while(-- argc){
			printf("%s", *++argv);
			do_ls(*argv);
		}
	return 0;
}
