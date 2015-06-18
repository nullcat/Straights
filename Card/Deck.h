#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <random>
#include <vector>

#include "Card.h"

using namespace std;

const int CARD_COUNT(52);   // mostly relayed to Deck class but may need to be used outside of deck class
const int DEAL_AMOUNT(13);  // same idea as CARD_COUNT

class Deck{
public:
    Deck();
    ~Deck();
	void shuffle();
	vector<Card*> dealCards();
	void printDeck() const;
    static int seed;
private:
    int deckDepth;  //tracks dealt cards, each time dealCards() is called, +13 to depth
	vector<Card*> cards_;
};

#endif
