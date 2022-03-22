#ifndef DESC_HPP
#define DESC_HPP

#include <stdio.h>
#include <stdlib.h>

#define MAX_DESK_GROUP 10

#include "group.hpp"
#include "game.hpp"

class Desk {
	Game *game;
	Cards *places;
	Cards **Case; // ?? maybe fix size and no fuck!
 public:
	Desk(Game *gptr);
	~Desk(void);
	int GetPlayerCount(void);
	Cards & GetPlayerPlace(int playerid);
	int CreateCardGroup(void); // pass coordinates
	Cards & GetCardGroup(int groupid);
	void DropCardGroup(int groupid);
};

#endif //DESC_HPP
