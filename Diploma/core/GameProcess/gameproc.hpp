#ifndef GAMEPROC_HPP
#define GAMEPROC_HPP

//It's the client's class!

#include "../NetProto/clientproto.hpp"
#include "datamanipulator.hpp"

class GameProc : public DataManipulator {
 protected:
	BigInt Conv;
	int waitnumber;
	ClientProtoToClient *clientproto;
/*!*/	//Player **playerstable;
 public:
	GameProc(ClientProtoToClient *cp, Game *mygame);
	~GameProc(void);
	int MainProcess(void);
	void ProcData(int playerid, int cmd, void * data);
	BigInt &CatchBigInt(void * data);
	//protected
	void SetProtoKeys(int playerid, void * data);
	
	//public
	void MainConnect(int playerid, void * data);
	void MainHello(int playerid, void * data);
	void MainReady(int playerid, void * data);
	void MentalAnswer(int playerid, void * data);
	void SendLog(int playerid);
	void ContinueGetCardsFromLog(void);
	unsigned short ClientInPort(void);
	virtual void TokenCards(int *cards, int size) = 0;
	virtual void TokenCards(int playerid, int size) = 0;
	virtual void OpenCards(int playerid, void *data) = 0;
	virtual void AddToPCards(int playerid, void *data) = 0;
	virtual void RemFromPCards(int playerid, void *data) = 0;
	virtual void AddToGCards(void *data) = 0;
	virtual void RemFromGCards(void *data) = 0;
	virtual void SetAssoc(int associd) = 0;
	virtual void SetAssoc(int playerid, int associd) = 0;
	virtual int GetAssoc(int playerid) = 0;
	virtual int GetPlayer(int associd) = 0;

	//functions pure definition for test
	virtual int CreateButton(int x, int y, int w, int h, char *text) = 0;
	virtual int SendMessageToAll(const char * msg) = 0;
	virtual int TogglePlayerSecureMode(int playerid, bool mode) = 0;
	virtual bool IsPlayerSecureMode(int playerid) = 0;

	//callbacks pure definition
	virtual int OnPlayerConnected(int playerid) = 0;
	virtual int OnPlayerRecvMessage(int playerid, const char *msg) = 0;
	virtual int OnPlayerSendMessage(const char *msg) = 0;
	virtual int OnPlayerCommand(const char *msg) = 0;
	virtual int OnPlayerReadyCheck(void) = 0;
	virtual int OnOtherReadyCheck(int playerid) = 0;
	virtual int OnPlayerStep(int playerid) = 0;
	virtual int OnStepFinish(void) = 0;
};

#endif
