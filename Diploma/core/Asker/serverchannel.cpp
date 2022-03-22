#ifndef SERVERCHANNEL_CPP
#define SERVERCHANNEL_CPP

#include "serverchannel.hpp"

/*class ServerChannel {
	GlobalSocket **clients;
	int slots, listener;
 public:*/

ServerChannel::ServerChannel(int port, int slotlimit){
	int i;
	struct sockaddr_in addr;
	slots = slotlimit;
	clients = new GlobalSocket*[slots];
	for(i=0; i<slots; i++)
		clients[i] = NULL;

    	listener = socket(AF_INET, SOCK_STREAM, 0);
    	if(listener < 0)
    	{
        	perror("socket");
        	exit(1);
    	}
    
    	addr.sin_family = AF_INET;
   	addr.sin_port = htons(port);
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    	{
        	perror("bind");
        	exit(2);
    	}

    	listen(listener, 3);
	active = 0;
}

ServerChannel::~ServerChannel(void){
	int i;
	//disconnecting
	for(i=0; i<slots; i++)
		if(clients[i]!=NULL)
			delete clients[i];
	//drop slots
	delete [] clients;
	//close listener
	close(listener);
}

void ServerChannel::MainProcess(void){
	char buffer[BUFFER_SIZE];
	int sock, i, k, s, cmd;
	fd_set tmpfd, listenerfd;
	struct timeval tv;
	srand(time(0));
	while(true){
		tv.tv_sec = 0;
		tv.tv_usec = 10000;
		FD_SET(listener, &listenerfd);
		select(listener+1, &listenerfd, NULL, NULL, &tv);
		if(FD_ISSET(listener, &listenerfd)){
			sock = accept(listener, NULL, NULL);
			clients[active++] = new GlobalSocket(sock);
			FD_SET(sock, &sockfd);
			maximum = 0;
			for(i=0; i<active; i++)
				if(maximum < (s = clients[i]->GetSock()))
					maximum = s;
			maximum++;
			cout << "connected!" << endl;
		}
		FD_ZERO(&listenerfd);
		tv.tv_sec = 0;
		tv.tv_usec = 10000;
		memcpy(&tmpfd, &sockfd, sizeof(fd_set));
		if(select(maximum, &tmpfd, NULL, NULL, &tv)<1)
			continue;
cout << "lala 1 " << endl;
		for(k=0; k<active; k++){
			if(FD_ISSET(clients[k]->GetSock(), &tmpfd)){
				cout << "lala 2" << endl;
				if(clients[k]->RecvData(cmd, buffer)!=0)
					this->ProcData(k, cmd, buffer);
				else ReleaseConnection(k--); // v ClientChannel error?
			}
		}
	}
}

void ServerChannel::ReleaseConnection(int clientid){
	int i,s;
	FD_CLR(clients[clientid]->GetSock(), &sockfd); // when lost connection
	delete clients[clientid];
	clients[clientid] = clients[--active]; //if active is one
	clients[active] = NULL;
	maximum = 0;
	for(i=0; i<active; i++)
		if(maximum < (s = clients[i]->GetSock()))
			maximum = s;
	maximum++;
}

#endif
