#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <ostream>
#include <istream>

#include "Player.h"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();                             // default constructor
    ComputerPlayer(const Player& player);    // copy contructor
    ~ComputerPlayer();
    Type makeMove(Table& table, Deck& deck,Command c); //Command is ignored as a computer player
    static bool intelligentAI;
};

#endif
