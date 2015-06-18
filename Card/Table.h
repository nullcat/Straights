#ifndef _TABLE_
#define _TABLE_

#include <ostream>
#include <istream>

using namespace std;

class Table{
public:
    void printTable() const;
    void addCard(Card card);
    Card findCard() const;             // used to check against cards from players
private:
    vector<Card> cards_;
};

#endif
