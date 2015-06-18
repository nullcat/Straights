#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>
#include <vector>

#include "Card.h"
#include "Table.h"

using namespace std;

class Player{
public:
    Player();
    ~Player();
	void printHand() const;             // although this is not required for computer player class, it makes sense to have this for any derivation of Player
	void printLegalPlays() const;       // print
    int getScore() const;               // accessor for score
    bool hasCard(Suit, Rank) const;     // There should only be one copy of every 52 cards, need to compare without creating a new card
    Card* findCard(Suit, Rank) const;   // attempts to find a card on hand
	virtual void makeMove(Table &table);        // decision making will be left up to derived classes
private:
    void discardCard(Card* card);
    void playCard(Card* card);
	int score_;
protected:
    void removeCard(Card* card);
    bool IsLegalPlay(Card* card);   //no matter the derived class, we should be allowed to check if a card is valid for this player
    void getNewLegalPlays(vector<Card*> tableCards);         //gets new set of legal plays, sets legalPlays_
    vector<Card*> hand_;
	vector<Card*> discards_;
	vector<Card*> legalPlays_;
};

#endif
