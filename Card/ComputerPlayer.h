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
    void makeMove(Table &table);
};

#endif