#ifndef _HUMANPLAYER_
#define _HUMANPLAYER_

#include <ostream>
#include <istream>

#include "Player.h"

using namespace std;

class HumanPlayer : public Player
{
public:
	HumanPlayer();
	~HumanPlayer();
	void printHand() const;
	Type makeMove(Table& table, Deck& deck,Card card);
};

#endif
