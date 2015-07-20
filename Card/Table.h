#ifndef _TABLE_
#define _TABLE_

#include <ostream>
#include <istream>
#include <vector>

#include "Card.h"


class Table{
public:
    void printTable() const;
    void addCard(Card card);
    void clearTable();
    bool isEmpty() const;
    std::vector<Card> getCardsOfSuit(Suit) const;   // used to check against cards from players
    std::vector<Card> getAllCards() const;
    friend std::ostream& operator << (std::ostream&, const Table&);
private:
    std::string getRanksString(std::vector<Card> cards) const;
    std::vector<Card> cards_;
};

#endif
