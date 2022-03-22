#ifndef SERVERCHANNEL_HPP
#define SERVERCHANNEL_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "../NetProto/globalsocket.hpp"
#include "../apilist.hpp"
#include <sys/select.h>
#include <time.h>

class ServerChannel {
	int slots, active, listener, maximum;
	fd_set sockfd;
 protected:
	GlobalSocket **clients;
 public:
	ServerChannel(int port, int slotlimit = 2);
	virtual ~ServerChannel(void);
	void MainProcess(void); // accept & sendto work()
	void ReleaseConnection(int clientid);
	virtual void ProcData(int clientid, int cmd, void *data) = 0;
};

#endif
