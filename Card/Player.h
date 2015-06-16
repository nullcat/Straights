#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>
#include <vector>

#include "Card.h"

using namespace std;

class Player{
public:
	vector<Card> getHand() const;
	void addToHand(Card card);
	void addCards(Card* card);
	virtual Card playCard(Card card);
private:
    void removeCard(Card Card);
    vector<Card> findCard(Card card) const;
	vector<Card> hand_;
};

#endif
