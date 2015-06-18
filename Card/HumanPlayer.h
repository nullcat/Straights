#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <ostream>
#include <istream>

#include "Player.h"

using namespace std;

class HumanPlayer : public Player
{
public:
	explicit HumanPlayer();
	Card playCard();
};

#endif
