#ifndef SCRIPTAPI_HPP
#define SCRIPTAPI_HPP

#include "gameproc.hpp"
#include "../apilist.hpp"

/* MACRO FOR memcpy operations */ // move to utils and make universal ??

#ifndef PUSHVAR
  #define PUSHVAR(__buff, __ptr, __size) \
	do { \
		memcpy(__buff, __ptr, (__size)); \
		__buff+=(__size); \
	} while(0)
#endif

#ifndef ASSERT
  #define ASSERT(__expr) \
	if(!__expt) { \
		printf("[%d] Error! %s\n", __LINE__, ##_expr); \
		output+=sizeof(int); \
	}
#endif

class ScriptApi : public GameProc {
 private:
	int *assoc_player, *player_assoc;
	int maxassocid, associated;
 protected:
	void (*backDoor)(int, void*);
	char output[256]; //?? need local for every call backDoor, else not safe for threads
 public:
	ScriptApi(/*void*/ ClientProtoToClient *cp, void (*BackDoor)(int, void*)); // Here main prepare
	~ScriptApi(void); // Destruct processes and objects
	void TokenCards(int *cards, int size);
	void TokenCards(int playerid, int size);
	void OpenCards(int playerid, void *data);
	void AddToPCards(int playerid, void *data);
	void RemFromPCards(int playerid, void *data);
	void AddToGCards(void *data);
	void RemFromGCards(void *data);
	void OpenCards(int *sel, int size);
	void SetAssoc(int associd);
	void SetAssoc(int playerid, int associd);
	int GetPlayer(int associd);
	int GetAssoc(int playerid);
	int GetMaxAssocid(void);
 //debug
	int Debug(void);
 //functions
	int SendMessageToAll(const char * msg); //void
	int TogglePlayerSecureMode(int playerid, bool mode); //void
	bool IsPlayerSecureMode(int playerid);
	int GetCardsFromLog(int number); //void
	//Assoc
	void InitAssoc(void);
	void NextStep(int playerid);
	void FinishStep(void);
	bool IsOwner(void);
	//Visual control API functional
	int CreateButton(int x, int y, int w, int h, char *text);
	void SetButtonText(int buttonid, char *text);
	void SetButtonEnabled(int buttonid, bool mode);
	void DropButton(int buttonid);
	int CreateGardsGroup(int x, int y, char *text);
	void SetCardsGroupText(int cgid, char *text);
	void SetCardsGroupXY(int cgid, int x, int y);
	void SetCardsGroupVertical(int cgid, bool mode);
	void SetCardsGroupControl(int cgid, bool mode);
	void SetCardsGroupEnabled(int cgid, bool mode);
	void DropCardsGroup(int cgid);
	void SetPlayerCardsXY(int playerid, int x, int y);
	void SetPlayerCardsVertical(int playerid, bool mode);
	void SetPlayerCardsControl(int playerid, bool mode);
	void SetPlayerCardsEnabled(int playerid, bool mode);
	int SizeSelPlayerCards(void);
	void GetSelPlayerCards(int *selcards);
	int SizeAllPlayerCards(void);
	void GetAllPlayerCards(int *selcards);
	void OpenPlayerCards(int *selcards, int size);
	void AddToPlayerCards(int *selcards, int size);
	void RemFromPlayerCards(int *selcards, int size);
	int SizeSelCardsGroup(int cgid);
	void GetSelCardsGroup(int cgid, int *selcards);
	int SizeAllCardsGroup(int cgid);
	void GetAllCardsGroup(int cgid, int *selcards);
	void AddToCardsGroup(int cgid, int *selcards, int size);
	void RemFromCardsGroup(int cgid, int *selcards, int size);
	void SetPlayerScore(int score);
 //callbacks
	virtual int OnPlayerConnected(int playerid);
	virtual int OnPlayerRecvMessage(int playerid, const char *msg);
	virtual int OnPlayerSendMessage(const char *msg);
	virtual int OnPlayerCommand(const char *msg); // Delete?
	virtual int OnPlayerReadyCheck(void);
	virtual int OnOtherReadyCheck(int playerid);
	virtual int OnPlayerStep(int playerid);
	virtual int OnStepFinish(void);
	virtual int OnAssociated(void);
};

#endif //SCRIPTAPI_HPP
