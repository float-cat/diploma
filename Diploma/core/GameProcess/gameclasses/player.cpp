#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"

	/*int virtualid;
	char * name;
	char * ipa;*/
	//ip_address;

Player::Player(char * Name, char * Ipa){
	name = new char[strlen(Name)+1];
	strcpy(name, Name);
	ipa = new char[strlen(Ipa)+1];
	strcpy(ipa, Ipa);
}

Player::~Player(void){
	delete [] name;
	delete [] ipa;
}

void Player::SetPort(unsigned short Port){
	port = Port;
}

char * Player::GetIPA(void){
	return ipa;
}

unsigned short Player::GetPort(void){
	return port;
}

char * Player::GetName(void){
	return name;
}

Cards & Player::GetPlayerHand(void){
	return OnHand;
}

#endif
