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
    void resumeRound(int position);
    bool gameEnded() const;
    bool roundEnded() const;
    vector<Card> getPlayerHand() const;
    vector<Card> getTableCards() const;
    vector<int> getPlayerScores() const;
    vector<int> getPlayerDiscards() const;
    int ragequit();
private:
    void printScores() const;
    int getStarterPlayerNumber() const;
    int getNextPlayerNumber(int) const;
    void dealDeck();
    void checkWinCondition();
    void printWinners() const;
    void playRound();
    void nextPlayer();

    bool endFlag_;
    bool roundEndFlag_;
    Player* convertToComputerPlayer(Player*);
    Table table_;
    Deck deck_;
    vector<Player*> players_;
    Player * currentPlayer_;
    int playerIndex_;
    int startingPlayerIndex_;
};

#endif
