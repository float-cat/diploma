#ifndef FORPAWN_HPP
#define FORPAWN_HPP

#include "scriptapi.hpp"

class ForPawn : public ScriptApi {
	/*Test Variable*/
	int /*KeyOpenCards, KeyGetCards, KeyAddScore, */KeyStepFinish;
	int score, nextplayer, step;
	char testtext[30];
	/*Test Variable*/
 public:
	ForPawn(/*void*/ ClientProtoToClient *cp, void (*BackDoor)(int, void*)); // Here main prepare
	~ForPawn(void); // Destruct processes and objects
 //callbacks
	int OnGameProcessStart(void);
	int OnGameProcessFinish(void);
	int OnGameStarted(void);
	int OnCtrlButtonClicked(int buttonid);
	int OnPlayerConnected(int playerid); //child
	int OnPlayerRecvMessage(int playerid, const char *msg); //child
	int OnPlayerSendMessage(const char *msg); //child
	int OnPlayerCommand(const char *msg); //child
	int OnPlayerReadyCheck(void); //child
	int OnOtherReadyCheck(int playerid); //child
	int OnPlayerStep(int playerid); //child
	int OnStepFinish(void); //child
	int OnAssociated(void);
};

#endif //FORPAWN_HPP
