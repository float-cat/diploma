#ifndef SERVERPROTO_HPP
#define SERVERPROTO_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//#include <mysql.h> //mysql support!

using namespace std;

#include "serverchannel.hpp"
#include "../apilist.hpp"
#include "../NetProto/commands.h"

class ServerProto : public ServerChannel {
	char output[BUFFER_SIZE];
	GameDataItem *root;
	ModeDataItem *modes;
 public:
	ServerProto(int port, int slotlimit = 2);
	~ServerProto(void);
	void ProcData(int clientid, int cmd, void *data);
	//
	void GameInfo(int clientid, GameData gamedata);
	void ModeInfo(int clientid, ModeData modedata);
	void ModeTransfer(int clientid, int fsize, char *fname);
	void ModePart(int clientid, int dsize, char *data);
	void ModeFinish(int clientid);
	void AnswerRegLog(int clientid, int status);
};

#endif
