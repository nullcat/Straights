#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>
#include <vector>

#include "Card.h"
#include "Table.h"
#include "Deck.h"
#include "Command.h"


class Player{
public:
    Player();
    ~Player();
    Player(const Player&);              //copy constructor
    void addCards(std::vector<Card> cards);  //add set of cards from deck
    void newRound();                    // resets hand, discards and updates scores
	virtual void printHand() const;     // although this is not required for computer player class, it makes sense to have this for any derivation of Player
	void printLegalPlays() const;       // print legal cards to play
	void printDiscardsAndScore() const; // print discards and score
	std::vector<Card> getLegalPlays() const;    //get all legal plays
	std::string getDiscardsAndScore() const;    //get all discards and scores
    int getScore() const;                   // accessor for score
    int getOldScore() const;                // accesspr for oldscore
    int getPlayerNumber() const;            // accessor
    bool hasCard(Card card) const;          // There should only be one copy of every 52 cards, need to compare without creating a new card
    std::vector<Card> getHand() const;      //accessor
    int getDiscards() const;                //get discards of player
	virtual Type makeMove(Table& table, Deck& deck,Command c) = 0; // decision making will be left up to derived classes, returns Command Type because game will want to know what command the player did which might impact the state of the game
	void playCard(Card card, Table &table);            // can be private for this game, but we should be allowed to call this from outside
    void discardCard(Card card); // can be private for this game, but we should be allowed to call this from outside
    static int NumberOfPlayers_;    // keeps track of number of players, used to assign player # on creating new players

private:
    void removeCard(Card card);
    int score_;                     // current score
    int oldScore_;                  // old score
    int playerNumber_;              // player number, used for printing
protected:
    void printCards(std::vector<Card>) const;
    std::string getCards(std::vector<Card>) const;
    void getNewLegalPlays(const Table &table);         //gets new set of legal plays, sets legalPlays_
    bool IsLegalPlay(Card card);   //no matter the derived class, we should be allowed to check if a card is valid for this player
    std::vector<Card> hand_;
	std::vector<Card> discards_;
	std::vector<Card> legalPlays_;
};

#endif
