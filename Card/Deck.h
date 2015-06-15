#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <random>

class Deck{
public:
	void shuffle();
	Card* dealCards();
private:
	Card* _cards;
};

#endif
