#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <stdlib.h>
#include "../../NetProto/clientchannel.hpp"

enum {
	//LOG_CUSTOM, //NOT SUPPORTED
	//LOG_36CARDS, //NOT SUPPORTED
	//LOG_52CARDS, //NOT SUPPORTED
	LOG_54CARDS
};

class Game {
	int logsize;
	ClientChannelToClient *channel;
 public:
	Game(ClientChannelToClient *cc);
	~Game(void);
	int CountPlayers(void);
	int GetLogSize(void);
	void IncLogSize(void);
};

#endif //GAME_HPP
