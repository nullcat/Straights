#ifndef _GAME_
#define _GAME_

#include <ostream>
#include <istream>

#include "Player.h"
#include "Table.h"
#include "Deck.h"

using namespace std;

const int MAX_SCORE(80);

class Game{
public:
    Game(vector<Player*>, Table&, Deck&);
    ~Game();
    void startNewRound();
    bool hasEnded() const;
private:
    void printScores() const;
    int getStarterPlayerNumber() const;
    void dealDeck();
    void checkWinCondition();
    bool endFlag_;
    Player* convertToComputerPlayer(Player*);
    Table table_;
    Deck deck_;
    vector<Player*> players_;
};

#endif
