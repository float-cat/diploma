#ifndef GAME_CPP
#define GAME_CPP

#include "game.hpp"

Game::Game(ClientChannelToClient *cc){
	channel = cc;
	logsize = 0;//test
}

Game::~Game(void){
	/**/
}

int Game::CountPlayers(void){
	return channel->SlotsUses();
}

int Game::GetLogSize(void){
	return logsize;
}

void Game::IncLogSize(void){
	logsize++;
}

#endif //GAME_CPP
