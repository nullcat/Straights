#ifndef _GAME_
#define _GAME_

/*
* Facade pattern, this object encapsulates all other objects and provide an interface to interact with part 1 logic
*/


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
    void resumeRound(Command c);                    //resume round with command from the view
    int ragequit();                                 //ragequit current player

    //accessors for the view
    bool gameEnded() const;
    bool roundEnded() const;
    std::vector<Card> getPlayerHand() const;
    std::vector<Card> getTableCards() const;
    std::vector<int> getPlayerScores() const;
    std::vector<int> getPlayerDiscards() const;
    std::string getWinners() const;
    std::string getResults() const;

    //bonus features
    std::vector<Card> getLegalPlays() const;
    int getCurrentPlayerPosition() const;

private:
    void printScores() const;
    void printWinners() const;
    void setStartingPlayerNumber();
    void dealDeck();
    void checkWinCondition();
    void playRound();                           //loop to play round until end or when user input is required
    void nextPlayer();                          //increment current play to next player
    Player* convertToComputerPlayer(Player*);   //for ragequit

    bool endFlag_;
    bool roundEndFlag_;
    Table table_;
    Deck deck_;
    std::vector<Player*> players_;
    Player * currentPlayer_;
    int startingPlayerIndex_;
};

#endif
