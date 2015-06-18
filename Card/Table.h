#ifndef _TABLE_
#define _TABLE_

#include <ostream>
#include <istream>
#include <vector>

#include "Card.h"

using namespace std;

class Table{
public:
    void printTable() const;
    void addCard(Card card);
    bool isEmpty() const;
    vector<Card> getCardsOfSuit(Suit) const;   // used to check against cards from players
private:
    void printRanks(vector<Card> cards) const;
    vector<Card> cards_;
};

#endif
