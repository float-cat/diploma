#ifndef DESC_CPP
#define DESC_CPP

#include "desk.hpp"

Desk::Desk(Game *gptr){
	game = gptr;
	places = new Cards[game->CountPlayers()];
	Case = new Cards*[MAX_DESK_GROUP];
	for(int i=0; i<MAX_DESK_GROUP; i++)
		Case[i] = NULL;
}

Desk::~Desk(void){
	delete [] places;
	for(int i=0; i<MAX_DESK_GROUP; i++)
		if(Case[i]!=NULL) delete Case[i];
	delete [] Case;
}

int Desk::GetPlayerCount(void){
	return game->CountPlayers();
}

Cards & Desk::GetPlayerPlace(int playerid){
	return places[playerid];
}

int Desk::CreateCardGroup(void){ // pass coordinates
	int i=0;
	while(i<MAX_DESK_GROUP)
		if(Case[i]==NULL) break;
		else i++;
	Case[i] = new Cards;
	return i;
}

Cards & Desk::GetCardGroup(int groupid){
	return *Case[groupid];
}

void Desk::DropCardGroup(int groupid){
	delete Case[groupid];
	Case[groupid] = NULL;
}

#endif //DESC_CPP
