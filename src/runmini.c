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
using namespace std;
#define WAY_NUM 16
#include <sys/time.h>
int main(int argc, char **argv)
{

	char buff[255];
	int fd = open(argv[1], O_RDWR, 0);  // O_RDWR 才能被讀寫。
	if (fd < 0)fprintf(stderr, "open: %s\n", strerror(errno));  // 使用異常檢查是個好習慣， 他可以幫助程序員迅速定位出錯的地方！

	struct timeval timeStart, timeEnd;
	gettimeofday(&timeStart,NULL);
	//int fd = open(argv[1], O_RDWR, 0);  // O_RDWR 才能被讀寫。
	int ret = read(fd,buff,255);
	//close(fd);
	gettimeofday(&timeEnd,NULL);
	long runTime = (timeEnd.tv_sec-timeStart.tv_sec)*1000000 + timeEnd.tv_usec - timeStart.tv_usec;
	cout<<"open read time:"<<runTime<<endl;	
	printf("read size: %d,buff:%s\n",ret,buff);
	char* tmp = strtok(buff,"\n");
	tmp = strtok(NULL,"\n");
	tmp = strtok(NULL,"\n");//skip the first two lines
	while(tmp != NULL){
		int way, used;
		printf("tmp:%s",tmp);
		sscanf(tmp,"%d,%d",&way,&used);
		printf("get:%d, %d\n",way,used);
		tmp = strtok(NULL,"\n");
	}
	close(fd);

	return 0;
}
