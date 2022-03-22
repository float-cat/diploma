#ifndef DATAMANIPULATOR_CPP
#define DATAMANIPULATOR_CPP

#include "datamanipulator.hpp"

DataManipulator::DataManipulator(int max, Game *mygame) : MentalPoker(mygame->GetLogSize()) {
	int i;
	maxslot = max;
	desk = NULL;
	game = mygame;
	playerstable = new Player*[maxslot];
	for(i=0; i<maxslot; i++)
		playerstable[i] = NULL;
	mainLog = new Cards;
}

DataManipulator::~DataManipulator(void){
	int i;
	for(i=0; i<maxslot; i++)
		if(playerstable[i] != NULL) delete playerstable[i];
	delete [] playerstable;
	delete mainLog;
}

int DataManipulator::AppendNewPlayer(int playerid, Player *p){
	playerstable[playerid] = p;
	//return p->VirtualId();
	return 0;
}

int DataManipulator::SetPlayerPort(int playerid, unsigned short port){
	playerstable[playerid]->SetPort(port);
}

bool DataManipulator::IsPlayerConnected(int playerid){
	return playerstable[playerid] != NULL;
}

char * DataManipulator::GetPlayerIP(int playerid){
	return playerstable[playerid]->GetIPA();
}

unsigned short DataManipulator::GetPlayerPort(int playerid){
	return playerstable[playerid]->GetPort();
}

char * DataManipulator::GetPlayerName(int playerid){
	return playerstable[playerid]->GetName();
}

int DataManipulator::GetMaxSlot(void){
	return maxslot;
}

//Base
int DataManipulator::GetPlayerCount(void){
	return desk->GetPlayerCount();
}

//Desk
int DataManipulator::OpenDesk(void){
	desk = new Desk(game);
	//api->DeskOpened();
}

int DataManipulator::InitLog(int mode){
	int i,j;
	for(i=0; i<4; i++)
		for(j=(mode != INIT_LOG_36)?0:4; j<13; j++)
			mainLog->Append(Card(i,j));
	if(mode == INIT_LOG_54){
		mainLog->Append(Card(SUIT_SPADES, NOMINAL_JOCKER));
		mainLog->Append(Card(SUIT_HEARTS, NOMINAL_JOCKER));
	}
}

//Group
int DataManipulator::AddGroupToPlayerHand(int playerid, int groupid){
	playerstable[playerid]->GetPlayerHand() = playerstable[playerid]->GetPlayerHand().Cons(desk->GetCardGroup(groupid)); // local optimal ?
}

int DataManipulator::RemGroupToPlayerHand(int playerid, int groupid){
	playerstable[playerid]->GetPlayerHand() = playerstable[playerid]->GetPlayerHand().Diff(desk->GetCardGroup(groupid)); // local optimal ?
}

int DataManipulator::CreateCardGroup(void){
	return desk->CreateCardGroup();
}

int DataManipulator::AddGroupToGroup(int descgid, int srcgid){
	desk->GetCardGroup(descgid) = desk->GetCardGroup(descgid).Cons(desk->GetCardGroup(srcgid));
}

int DataManipulator::RemGroupToGroup(int descgid, int srcgid){
	desk->GetCardGroup(descgid) = desk->GetCardGroup(descgid).Diff(desk->GetCardGroup(srcgid));
}

void DataManipulator::DropCardGroup(int groupid){
	desk->DropCardGroup(groupid);
}

#endif
