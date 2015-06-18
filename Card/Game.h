#ifndef _GAME_
#define _GAME_

#include <ostream>
#include <istream>

using namespace std;

const int MAX_SCORE(80);

class Game{
public:
    Player find7SPlayer(Player* players);
    void playRound();
private:
};

#endif
