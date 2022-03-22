#ifndef FORPAWN_HPP
#define FORPAWN_HPP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>     /* for memset() (on some compilers) */
#if defined __WIN32__ || defined _WIN32 || defined WIN32
  #include <malloc.h>
#endif
#include "amx/amx.h"
#include "amx/amxgc.h"
#include "amx/amxaux.h"
#include "scriptapi.hpp"

class ForPawn : public ScriptApi {
	AMX amx;
	static char *strbuffer;
	static ForPawn *pScript;
 //functional
	static cell AMX_NATIVE_CALL n_CreateButton(AMX* amx, const cell* params);
	static cell AMX_NATIVE_CALL n_DebugFunc(AMX* amx, const cell* params);
 public:
	ForPawn(/*void*/ ClientProtoToClient *cp, void (*BackDoor)(int, void*), char *script); // Here main prepare
	~ForPawn(void); // Destruct processes and objects
	/*Test Functional*/
	/*Test Functional*/
 //callbacks
	int OnGameProcessStart(void);
	int OnGameProcessFinish(void);
	int OnGameStarted(void);
	//int OnGameFinished(void);
	//int OnPlayerWin(int playerid);
	int OnCtrlButtonClicked(int buttonid);
	int OnPlayerConnected(int playerid);
	//int OnPlayerDisconnected(int playerid);
	int OnPlayerRecvMessage(int playerid, const char *msg);
	int OnPlayerSendMessage(const char *msg);
	int OnPlayerCommand(const char *msg);
	int OnPlayerReadyCheck(void);
	int OnOtherReadyCheck(int playerid);
	int OnPlayerStep(int playerid);
	int OnStepFinish(void);
	int OnAssociated(void);
};

#endif //FORPAWN_HPP
