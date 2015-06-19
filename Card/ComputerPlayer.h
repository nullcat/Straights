#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <ostream>
#include <istream>

#include "Player.h"

using namespace std;

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();                             // default constructor
    ComputerPlayer(const Player& player);    // copy contructor
    ~ComputerPlayer();
    Type makeMove(Table& table, Deck& deck);
};

#endif
