#ifndef CLIENTCHANNEL_HPP
#define CLIENTCHANNEL_HPP

#include "globalsocket.hpp"
#include <arpa/inet.h>

class ClientChannelToClient;

class ClientChannelToServer {
	fd_set sockfd;
 protected:
	GlobalSocket *mysock;
 public:
	ClientChannelToServer(void); // ip + port
	virtual ~ClientChannelToServer(void);
	void MainProcess(void);
	virtual void ProcData(int cmd, void *databuf) = 0;
};

class ClientChannelToClient {
	bool actor;
 protected:
	GlobalSocket **clients;
	int slots, listener, maximum;
        fd_set sockfd;
	unsigned short in_port;
 public:
	virtual void Connected(int playerid) = 0;
	ClientChannelToClient(void);
	virtual ~ClientChannelToClient(void);
	int Connect(/*IP,*/int port);
	void MainProcess(void);
	int AllPlayer(int * array);
	int AskReady(int * array);
	void ReleaseConnection(int slotid);
	char *SlotIPA(int slotid);
	int SlotsUses(void);
	unsigned short GetInPort(void);
};

#endif
