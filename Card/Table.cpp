#include <iostream>
#include <sstream>
#include <algorithm>
#include "Table.h"
#include "Deck.h"

void Table::addCard(Card card)
{
    cards_.push_back(card);
}

vector<Card> Table::getCardsOfSuit(Suit suit) const
{
    vector<Card> suitCards;

    for(int i=0;i<cards_.size();i++)
    {
        if(cards_[i].getSuit()==suit)
            suitCards.push_back(cards_[i]);
    }

    return suitCards;
}

void Table::clearTable()
{
    cards_.clear();
}

bool Table::isEmpty() const
{
    return cards_.empty();
}

string Table::getRanksString(vector<Card> cards) const
{
    string ranks;

    vector<Card> sortedCards = cards;
    sort(sortedCards.begin(), sortedCards.end());


    for(int i=0;i<sortedCards.size();i++)
    {
        stringstream ss;
        ss << sortedCards[i].getRank()+1;
        ranks += ss.str();

        if(i != sortedCards.size()-1) //do not space at the end
            ranks += " ";
    }

    return ranks;
}

ostream& operator << (ostream &os, const Table &t)
{
    os << "Cards on the table:" << endl;
    os << "Clubs:" << t.getRanksString(t.getCardsOfSuit(CLUB)) << endl;
    os << "Diamonds:" << t.getRanksString(t.getCardsOfSuit(DIAMOND)) << endl;
    os << "Hearts:" << t.getRanksString(t.getCardsOfSuit(HEART)) << endl;
    os << "Spades:" << t.getRanksString(t.getCardsOfSuit(SPADE)) << endl;

    return os;
}
