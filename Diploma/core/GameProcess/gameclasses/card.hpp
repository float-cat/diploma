#ifndef CARD_HPP
#define CARD_HPP

#include <stdio.h>
#include <stdlib.h>

enum {
	SUIT_SPADES, // piki
	SUIT_HEARTS, // chervy
	SUIT_CLUBS, // kresti
	SUIT_DIAMONDS, // bubny
	SUIT_NONE = 0xFF
};

enum {
	NOMINAL_TWO,
	NOMINAL_THREE,
	NOMINAL_FOUR,
	NOMINAL_FIVE,
	NOMINAL_SIX,
	NOMINAL_SEVEN,
	NOMINAL_EIGHT,
	NOMINAL_NINE,
	NOMINAL_TEN,
	NOMINAL_JACK,
	NOMINAL_QUEEN,
	NOMINAL_KING,
	NOMINAL_ACE,
	NOMINAL_JOCKER,
	NOMINAL_NONE = 0xFF
};

/*char SuitName[4][9] = {
	"spades", "hearts", "clubs", "diamonds"
};

char NominalName[14][7] = {
	"two", "three", "four", "five", "six",
	"seven", "eight", "nine", "ten", "jack",
	"queen", "king", "ace", "jocker"
};
*/
class Card {
	short suit, nominal, log;
 public:
	Card(short Suit, short Nominal, short Log = 0);
	Card(void);
	//~
	void DebugPrintName(void);
	short GetSuit(void);
	short GetNominal(void);
	short GetLog(void);
};

#endif //CARD_HPP
