#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <vector>
#include <random>
#include "Card.h"
#include

//using namespace std;

const int CARD_COUNT(52);   // mostly relayed to Deck class but may need to be used outside of deck class
const int DEAL_AMOUNT(13);  // same idea as CARD_COUNT

class Deck{
public:
    Deck();
    ~Deck();
    void reset();
	void shuffle();
	std::vector<Card> dealCards();
    static int seed;
    static std::mt19937 rng;
    friend std::ostream& operator << (std::ostream&, const Deck&);
private:
    int deckDepth;  //tracks dealt cards, each time dealCards() is called, +13 to depth
	std::vector<Card> cards_;
};

#endif
