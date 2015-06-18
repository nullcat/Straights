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
	virtual void printHand() const;             // although this is not required for computer player class, it makes sense to have this for any derivation of Player
	void printLegalPlays() const;       // print
	vector<Card> getHand() const;
	vector<Card> getDiscards() const;
    int getScore() const;                   // accessor for score
    bool hasCard(Card card) const;          // There should only be one copy of every 52 cards, need to compare without creating a new card
    //Card findCard(Card card) const;       // attempts to find a card on hand
	virtual void makeMove(Table &table) = 0;        // decision making will be left up to derived classes
	void playCard(Card card, Table &table);            // can be private for this game, but we should be allowed to call this from outside
    void discardCard(Card card); // can be private for this game, but we should be allowed to call this from outside
private:
    void removeCard(Card card);
protected:
    int score_;
    void printCards(vector<Card>) const;
    void getNewLegalPlays(const Table &table);         //gets new set of legal plays, sets legalPlays_
    bool IsLegalPlay(Card card);   //no matter the derived class, we should be allowed to check if a card is valid for this player
    vector<Card> hand_;
	vector<Card> discards_;
	vector<Card> legalPlays_;
};

#endif
