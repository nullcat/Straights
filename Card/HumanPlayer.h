#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <ostream>
#include <istream>
#include <string>

#include "Player.h"


class HumanPlayer : public Player
{
public:
	HumanPlayer();
	~HumanPlayer();
	void printHand() const;
	Type makeMove(Table& table, Deck& deck,Command c);
};

#endif
