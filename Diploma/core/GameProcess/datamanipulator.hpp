#ifndef DATAMANIPULATOR_HPP
#define DATAMANIPULATOR_HPP

#include "mentalpoker.hpp"
#include "gameclasses/player.hpp"
#include "gameclasses/desk.hpp"
#include "gameclasses/game.hpp"

enum {
	INIT_LOG_36,
	INIT_LOG_52,
	INIT_LOG_54
};
/*
	players 1->1 group 1->* cards
	desk 1->* group 1->* cards
	1|->1 game  
*/

class DataManipulator : public MentalPoker {
 private:
	int maxslot;
	Player **playerstable;
	Desk *desk;
	Game *game;
	Cards *mainLog;
 protected:
	DataManipulator(int max, Game *mygame);
	~DataManipulator(void);
	//Player
	int AppendNewPlayer(int playerid, Player *p);
	int SetPlayerPort(int playerid, unsigned short port);
	bool IsPlayerConnected(int playerid);
	char * GetPlayerIP(int playerid);
	unsigned short GetPlayerPort(int playerid);
	char * GetPlayerName(int playerid);
	int GetMaxSlot(void);
	//Base
	int GetPlayerCount(void); //api
	//Desk
	int OpenDesk(void);
	int InitLog(int mode);
	//Group
	//Cards & GetPlayerPlace(int playerid);
	//int AddCardToPlayerHand(Card &src); //
	//int AddGroupToPlayerHand(int playerid, int groupid); //api
	//int RemGroupToPlayerHand(int playerid, int groupid); //api
	int AddGroupToPlayerHand(int playerid, int groupid); //api
	int RemGroupToPlayerHand(int playerid, int groupid); //api
	int CreateCardGroup(void); // pass coordinates : api
	//Cards & CreateCardCroup(int groupid);*/ // with lonely card ?
	int AddGroupToGroup(int descgid, int srcgid); //api
	int RemGroupToGroup(int descgid, int srcgid); //api
	void DropCardGroup(int groupid); //api
	/*
Operacii s gryppami kart
Operacii po iz'jatiu kart (md grypp)
Operacii po dobavleniu kart (md grypp)
Organizacija etalonnih kart (koloda i sravnenie)
	*/
 public://API
	//
};

#endif
