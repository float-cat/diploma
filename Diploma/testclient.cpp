#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

//Test -- on
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
//Test -- off

#include "core/corezombie.hpp"
#include <semaphore.h>

void BackDoor(int a, void * data){
}

//using namespace std;

int main(int argc, char *argv[])
{
	unsigned short in_port, con_port;
	CoreZombie core1(BackDoor);
	in_port = core1.ClientInPort();
	
	//Test -- on
int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(sock, &in_port, sizeof(unsigned short), 0);
    recv(sock, &con_port, sizeof(unsigned short), 0);
    
    close(sock);
	//Test -- off
	if(argc>1)
		core1.SetPlayerNick(argv[1]);
	if(con_port > 0)
		core1.Port(con_port);
	core1.Init();
	sem_t lock;
	sem_init(&lock, 0, 0);
	sem_wait(&lock);
	return 0;
}
