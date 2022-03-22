#ifndef CLIENTCHANNEL_CPP
#define CLIENTCHANNEL_CPP

#include "clientchannel.hpp"

ClientChannelToServer::ClientChannelToServer(void){ //razedinjaemie?
    int sock;
    BigInt::InitClass();
    mysock = NULL;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(10001); ///
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    mysock = new GlobalSocket(sock);
    FD_SET(sock, &sockfd); 
}

ClientChannelToServer::~ClientChannelToServer(void){
    delete mysock;
}

void ClientChannelToServer::MainProcess(void){ //recv!
    int cmd; char databuf[1024];
    fd_set tmpfd;
    struct timeval tv;
    while(true){
	tv.tv_sec = 0;
	tv.tv_usec = 10000;
	memcpy(&tmpfd, &sockfd, sizeof(fd_set));
	if(select(mysock->GetSock()+1, &tmpfd, NULL, NULL, &tv)==0)
		continue;
	if(FD_ISSET(mysock->GetSock(), &tmpfd)){
		if(mysock->RecvData(cmd, databuf)<1) break;
		this->ProcData(cmd, databuf);
	}
    }
}

//GlobalSocket **clients;
//int slots, listener;

ClientChannelToClient::ClientChannelToClient(void){
	int i;
	actor = true;
	struct sockaddr_in addr;
	slots = 5;
	clients = new GlobalSocket*[slots];
	for(i=0; i<slots; i++)
		clients[i] = NULL;

    	listener = socket(AF_INET, SOCK_STREAM, 0);
    	if(listener < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

	in_port = rand()%3000+1024;
    
    	addr.sin_family = AF_INET;
   	addr.sin_port = htons(in_port); // debug !
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    	{
        	perror("bind");
        	exit(2);
    	}

    	listen(listener, 3);
}

ClientChannelToClient::~ClientChannelToClient(void){
	for(int i=0; i<slots; i++)
		delete clients[i];
	delete [] clients;
}

int ClientChannelToClient::Connect(/*IP,*/int port){
	struct sockaddr_in addr;
	int sock, i, s;
	int result;
    	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(port); ///
    	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    	{
        	perror("connect");
        	exit(2);
    	}

	for(i=0; i<slots && clients[i]!=NULL; i++);

	result = i;

   	clients[i] = new GlobalSocket(sock);
	FD_SET(sock, &sockfd);
	actor = false;
	maximum = 0;
	for(i=0; i<slots; i++)
		if(clients[i]!=NULL && maximum < (s = clients[i]->GetSock()))
			maximum = s;
	maximum++;
	return result;
}

void ClientChannelToClient::MainProcess(void){ // whr disconnect?
	int sock, i, k, s;
	fd_set /*tmpfd,*/ listenerfd;
	struct timeval tv;
	srand(time(0));
	while(true){
		//if(actor){
			tv.tv_sec = 0;
			tv.tv_usec = 10000;
			FD_SET(listener, &listenerfd); // need everytime ? if(tralyalya)
			select(listener+1, &listenerfd, NULL, NULL, &tv);
			if(FD_ISSET(listener, &listenerfd)){
				sock = accept(listener, NULL, NULL);
				for(i=0; i<slots && clients[i]!=NULL; i++);
				clients[i] = new GlobalSocket(sock);
				FD_SET(sock, &sockfd);
				maximum = 0;
				//
				this -> Connected(i);
				//
				for(i=0; i<slots; i++)
					if(clients[i]!=NULL && maximum < (s = clients[i]->GetSock()))
						maximum = s;
				maximum++;
			}
			FD_ZERO(&listenerfd);
		//}
				//cout << "Iter: " << endl;
				//fflush(stdout);
		//cout << "actor " << (actor?"true":"false") << endl;
		/*if(!actor) {
			sleep(1);
			for(k=0; k<slots; k++){
				if(clients[k]!=NULL){
					cout << "p2p: ";
					clients[k]->SendData(NULL, 0);
				}
			}
			continue;
		}
		memcpy(&tmpfd, &sockfd, sizeof(fd_set));
		if(select(maximum, &tmpfd, NULL, NULL, &tv)==0)
			continue;
		for(k=0; k<slots; k++){
			int testrand = rand()%10;
			if(clients[k]!=NULL && FD_ISSET(clients[k]->GetSock(), &sockfd)){
				cout << "p2p: ";
				fflush(stdout);
				if(clients[k]->RecvData(NULL, 0)!=0){
					cout << "complete receive!" << endl;
					fflush(stdout);
					continue;
				}
				FD_CLR(clients[k]->GetSock(), &sockfd);
	    			delete clients[k];
				clients[k] = NULL;
				maximum = 0;
				for(i=0; i<slots; i++)
					if(clients[i]!=NULL && maximum < (s = clients[i]->GetSock()))
						maximum = s;
				maximum++; 
			}
		}*/
	}
}

int ClientChannelToClient::AllPlayer(int * array){ // ?? What doing this function?
	int result = 0, i;
	for(i=0; i<slots; i++){
		if(clients[i]!=NULL)
			array[result++] = i;
	}
	return result;
}

int ClientChannelToClient::AskReady(int * array){
	fd_set tmpfd;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10000;
	int result = 0, i;
	array[0] = 0; //?
	memcpy(&tmpfd, &sockfd, sizeof(fd_set));
	if(select(maximum, &tmpfd, NULL, NULL, &tv)==0)
		return 0;
	for(i=0; i<slots; i++){
		if(clients[i]!=NULL && FD_ISSET(clients[i]->GetSock(), &tmpfd))
			array[result++] = i;
	}
	return result;
}

void ClientChannelToClient::ReleaseConnection(int slotid){
	int i,s;
	FD_CLR(clients[slotid]->GetSock(), &sockfd);
	delete clients[slotid];
	clients[slotid] = NULL;
	maximum = 0;
	for(i=0; i<slots; i++)
		if(clients[i]!=NULL && maximum < (s = clients[i]->GetSock()))
			maximum = s;
	maximum++;
}

char * ClientChannelToClient::SlotIPA(int slotid){
	struct sockaddr_in addr;
	getsockname(clients[slotid]->GetSock(), (struct sockaddr*)&addr, 0);
	return inet_ntoa ((in_addr) addr.sin_addr);
}

int ClientChannelToClient::SlotsUses(void){
	int i,result = 0;
	for(i=0;i<slots;i++)
		if(clients[i] != NULL)
			result++;
	return result;
}

unsigned short ClientChannelToClient::GetInPort(void){
	return in_port;
}

#endif
