#ifndef _DECK_
#define _DECK_

#include <ostream>
#include <istream>
#include <random>
#include <vector>

#include "Card.h"

using namespace std;

const int seed(0);
const int CARD_COUNT(52);
const int DEAL_AMOUNT(13);

class Deck{
public:
	void shuffle();
	vector<Card> dealCards();
private:
	vector<Card> cards_;
};

#endif
