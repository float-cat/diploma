#ifndef CLIENTPROTO_HPP
#define CLIENTPROTO_HPP

#include "clientchannel.hpp" // object file
#include "../BigInt/biginteger.hpp" // object file
#include "commands.h" // cmd_ids
#include "../apilist.hpp"
#include <string.h>
//#include "md5.hpp"

class ClientProtoToClient;
class ClientProtoToServer;

class ClientProtoToServer : public ClientChannelToServer {
	char output[BUFFER_SIZE], protobuf[BUFFER_SIZE];
	void (*askerDoor)(int, void*);
	char *fname; FILE *pf; int fsize;
 public:
	ClientProtoToServer(void (*AskerDoor)(int, void*));
	~ClientProtoToServer(void);
	void ProcData(int cmd, void *databuf);
	//
	void NewGame(GameData gamedata); //CMD_NEWGAME
	void Release(void); //CMD_RELEASE
	void GameList(char *mode); //CMD_GAMELIST, //NO <Mode>
	void ModeList(void); //CMD_MODELIST // <Void>
	void GetMode(char *mode); //CMD_GETMODE //NO <Name>
	void Register(RegData regdata);
	void Login(RegData regdata); //NO <Data>
};

class ClientProtoToClient : public ClientChannelToClient {
	char * buffer;
	bool ishostage;
	int * readylist;
	int /*slots, */readynumber;
	// Debug
	char nick[30];
 public:
	ClientProtoToClient(void);
	virtual ~ClientProtoToClient(void);
	//
	int Connect(int port); // ip here?
	//int Disconnect(void); //Disconnected from Table
	//
	void SecurityMode(int playerid);
	void UnDefendedMode(int playerid);
	void NewKeys(int playerid);
	void MentalKey(int playerid, BigInt &Data);
	void ConfirmOfReady(int playerid);
	void LogControl(int playerid);
	void DecodeControl(int playerid);
	void SendIdxModel(int playerid, BigInt &Data);
	void SendIdxReal(int playerid, BigInt &Data);
	void SendIdxOnHand(int playerid, BigInt &Data);
	void OnHandUpdate(int playerid);
	void OnHandSecret(int playerid, int size);
	void OnHandOpen(int playerid, int *data, int size);
	void MentalBack(int playerid, int number);
	void GetLog(int playerid);
	void EndLog(int playerid);
	void PassCardPhys(int playerid, BigInt &Data);
	void PassCardVis(int playerid, int number); //??
	void SendMsg(int playerid, const char * msg);
	void Connect(int playerid, char * ipa, unsigned short port);
	void Hello(int playerid, char * name, int datasize, char * data);
	void Ready(int playerid);
	void Check(int playerid/*, md5*/);
	void Ok(int playerid);
	void Cancel(int playerid);
	void Error(int playerid, int errcode);
	void Noop(int playerid);
	void StepYourId(int playerid, int associd); //CMD_STEP_YOUR_ID,
	void StepI(int playerid, int associd); //CMD_STEP_I,
	void StepNow(int playerid, int associd); //CMD_STEP_NOW,
	void StepFinish(int playerid); //CMD_STEP_FINISH
	void AddToPlayerCards(int playerid, int *selcards, int size); //CMD_ADDTOPLAYER //Nado?
	void RemFromPlayerCards(int playerid, int *selcards, int size); //CMD_REMFROMPLAYER //Nado?
	void AddToCardsGroup(int playerid, int cgid, int *selcards, int size); //CMD_ADDTOGROUP
	void RemFromCardsGroup(int playerid, int cgid, int *selcards, int size); //CMD_REMFROMGROUP
	//
	int PlayerList(void);
	int GetPlayer(int idx);
	int ReadyList(void);
	int ReadyPlayer(int idx);
	int Catch(int playerid, void * data);
	int SetKeys(int playerid, char * data);
	int SetClientMode(int playerid, bool mode);
	bool GetClientMode(int playerid);
	int MaximumSlots(void);
	char *GetNick(void);
	void SetNick(const char *Nick);
	bool IsHostage(void);
	//callbacks
	void Connected(int playerid);
	//
	int GetPlayerSock(int playerid);
};

#endif
