#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
using namespace std;
#define WWS_SIZE 32768*100 // 2M; 2048 set; 64 B per cache line; 32768 cache line
int runRound = 0;
struct CacheLine{
	double a[8];
};
CacheLine* wws;
int fd = 0;
unsigned char* map_base;
unsigned char* map_base1;
void exit_pro(int signo){
	cout<<"now runRound:"<<runRound<<endl;
	delete [] wws;
	wws = NULL;
	exit(0);
	//close(fd);
	//munmap(map_base,WWS_SIZE*32);
	//munmap(map_base1,WWS_SIZE*32);
}
int main(int argc, char* argv[]){

	signal(SIGINT, exit_pro);
	if(argc < 3){
		cout<<"param number error\n";
		return -1;
	}
	int round = atoi(argv[1]);
	int intervel = atoi(argv[2]);
	wws = new CacheLine[WWS_SIZE];
	
	/*cout<<"start open\n";
	fd = open("/dev/mem",O_RDWR);
	if(fd == -1){
	cout<<"open file wrong\n";
	return -1;
	}
	cout<<"open dev/mem success\n";
	
	char rdbuff[20];
	int ret = read(fd,rdbuff,10);
	if(ret == -1){
	cout<<"read fail\n";
	close(fd);
	return -1;
	}
	for(int i=0;i<10;i++){
	printf("mem %d:%c",i,*(rdbuff+i));
	}

	map_base = (unsigned char*)mmap(NULL,WWS_SIZE/10*32,PROT_READ,MAP_PRIVATE,fd,0);
	//map_base1 = (unsigned char*)mmap(NULL,WWS_SIZE*32,PROT_READ,MAP_PRIVATE,fd,WWS_SIZE*32);
	if(map_base == MAP_FAILED || map_base1 == MAP_FAILED){
		cout<<"mmap fail\n";
	exit_pro(0);
	return -1;
	}
*/
	while(runRound < round){
		for(int i=0;i<WWS_SIZE;i++){
			/*for(int k=0;k<64;k++){
				unsigned char tmp = map_base[i*64+k];
			}*/
			for(int k=0;k<8;k++){
			  double tmp = ((wws[i]).a)[k];
			  }
			//wws[i] = rand()%100;

			for(int j =0;j<100*intervel;j++){}
		}
		//cout<<"round finished"<<endl;
		runRound++;
	}
	exit_pro(0);

	return 0;
}
