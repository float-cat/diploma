#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

#include "group.hpp"

class Player {
	int virtualid; //??
	unsigned short port;
	char * name;
	char * ipa;
	//ip_address;
	Cards OnHand;
 public:
	Player(char * Name, char * Ipa);
	~Player(void);
	void SetPort(unsigned short Port);
	char * GetIPA(void);
	unsigned short GetPort(void);
	char * GetName(void);
	Cards & GetPlayerHand(void);
};

#endif
