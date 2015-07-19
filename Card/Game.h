#ifndef _GAME_
#define _GAME_

#include <ostream>
#include <istream>

#include "Player.h"
#include "Table.h"
#include "Deck.h"

const int MAX_SCORE(80);


class Game{
public:
    Game(std::vector<Player*>, Table&, Deck&);
    ~Game();
    void startNewRound();
    void resumeRound(int position);
    bool gameEnded() const;
    bool roundEnded() const;
    std::vector<Card> getPlayerHand() const;
    std::vector<Card> getTableCards() const;
    std::vector<int> getPlayerScores() const;
    std::vector<int> getPlayerDiscards() const;
    std::string getWinners() const;
    std::string getResults() const;
    int ragequit();

    std::vector<Card> getLegalPlays() const; //bonus feature
    int getCurrentPlayerPosition() const;

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
    std::vector<Player*> players_;
    Player * currentPlayer_;
    int playerIndex_;
    int startingPlayerIndex_;
};

#endif
