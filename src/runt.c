//#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
//#include "csapp.h"
//#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <vector>
using namespace std;
#define WAY_NUM 16
//#define DEBUG
#ifdef DEBUG
#include <sys/time.h>
#endif

/*void mmapcopy(int fd, int size)
  {
  char *bufp;
  printf("fd:%d,size:%d\n",fd,size);
  bufp = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (bufp == (void *)-1)
  fprintf(stderr, "mmap: %s\n", strerror(errno));

//memcpy(bufp, "Linuxdd", 7);
printf("read:%s",bufp);
//write(1, bufp, size);
munmap(bufp, size);
return;
}*/
vector<int> fds;
ofstream* outFiles;
int fileNum;
void exit_pro(int signo){
	for(int i=0;i<fileNum;i++){
		close(fds[i]);
		outFiles[i].close();
	}
	delete[] outFiles;
	exit(0);
}

int main(int argc, char **argv)
{
	//struct stat stat;
	//fstat(fd, &stat);
	signal(SIGINT, exit_pro);
	if (argc < 4)
	{
		printf("error.\n");
		exit(0);
	}
	fileNum = argc - 3;
	outFiles = new ofstream[fileNum];
	char buff[255];
	//char to_write[] = "3\n";
	//write(fd,to_write,sizeof(to_write));
	//fsync(fd);
	int interval = atoi(argv[1]);//in microseconds
	int number = atoi(argv[2]);//record how many
	cout<<"will record: "<<number<<" pieces in "<<interval<<" us\n";
	for(int i=0;i<fileNum;i++){
	printf("read file:%s\n",argv[i+3]);
	}
	for(int i=0;i<fileNum;i++){
		cout<<"read file:"<<i<<endl;
		int fd = open(argv[i+3], O_RDWR, 0);  // O_RDWR 才能被讀寫。
		if (fd < 0){
			fprintf(stderr, "open: %s\n", strerror(errno));  // 使用異常檢查是個好習慣， 他可以幫助程序員迅速定位出錯的地方！
			return -1;
		}
		fds.push_back(fd);
		outFiles[i].open("record"+to_string(i)+".csv", ios::trunc);
	}
	int count = 0;
	int roundRecord[WAY_NUM];


	cout<<"open finished, start record\n";
	while(count < number){
		for(int j=0;j<fileNum;j++){
#ifdef DEBUG
			struct timeval timeStart, timeEnd;
			gettimeofday(&timeStart,NULL);
#endif
			//int fd = open(argv[1], O_RDWR, 0);  // O_RDWR 才能被讀寫。
			int ret = read(fds[j],buff,255);
			//close(fd);
#ifdef DEBUG
			cout<<"read finished\n";
			gettimeofday(&timeEnd,NULL);
			long runTime = (timeEnd.tv_sec-timeStart.tv_sec)*1000000 + timeEnd.tv_usec - timeStart.tv_usec;
			cout<<"open read time:"<<runTime<<endl;	
			printf("read size: %d,buff:%s\n",ret,buff);
#endif
			lseek(fds[j],SEEK_SET,0);

			char* tmp = strtok(buff,"\n");
			tmp = strtok(NULL,"\n");
			tmp = strtok(NULL,"\n");//skip the first two lines
			while(tmp != NULL){
				int way, used;
#ifdef DEBUG
				printf("tmp:%s",tmp);
#endif
				sscanf(tmp,"%d,%d",&way,&used);
#ifdef DEBUG
				printf("get:%d, %d\n",way,used);
#endif
				roundRecord[way] = used;
				tmp = strtok(NULL,"\n");
			}
			for(int i=0;i<WAY_NUM-1;i++){
				outFiles[j] << roundRecord[i]<<',';
			}
			outFiles[j] << roundRecord[WAY_NUM-1]<<'\n';
		}
		usleep(interval);
		count++;

	}
	exit_pro(0);	
	return 0;
}
