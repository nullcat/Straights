#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>

class Player{
public:
	Card* getHand() const;
	void addToHand(Card card);
	void addCards(Card* card);
	Card* playCard(string cardID);
private:
    findCard(Card::Rank, Card::Suit);
    removeCard(Card::Rank, Card::Suit);
	Card* _hand;
};

#endif
