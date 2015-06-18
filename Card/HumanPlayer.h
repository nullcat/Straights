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
	void makeMove(Table &table);
};

#endif
