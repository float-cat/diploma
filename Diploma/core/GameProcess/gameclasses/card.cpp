#ifndef CARD_CPP
#define CARD_CPP

#include "card.hpp"

char SuitName[4][9] = {
	"spades", "hearts", "clubs", "diamonds"
};

char NominalName[14][7] = {
	"two", "three", "four", "five", "six",
	"seven", "eight", "nine", "ten", "jack",
	"queen", "king", "ace", "jocker"
};

Card::Card(short Suit, short Nominal, short Log){
	suit = Suit;
	nominal = Nominal;
	log = Log;
}

Card::Card(void){
	suit = SUIT_NONE;
	nominal = NOMINAL_NONE;
	log = -1;
}

//~

void Card::DebugPrintName(void){
	printf("%s %s\n", NominalName[nominal], SuitName[suit]);
}

short Card::GetSuit(void){
	return suit;
}

short Card::GetNominal(void){
	return nominal;
}

short Card::GetLog(void){
	return log;
}

#endif //CARD_CPP
