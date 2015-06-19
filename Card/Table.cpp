#include <iostream>

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

    for(int i=0;i<cards.size();i++)
    {
        ranks += (int)cards[i].getRank() + " ";
    }

    return ranks;
}

ostream& operator << (ostream &os, const Table &t)
{

    os << "Cards on the table:" << endl;
    os << "Clubs: " << t.getRanksString(t.getCardsOfSuit(CLUB)) << endl;
    os << "Diamonds: " << t.getRanksString(t.getCardsOfSuit(DIAMOND)) << endl;
    os << "Hears: " << t.getRanksString(t.getCardsOfSuit(HEART)) << endl;
    os << "Spades: " << "7" << endl;

    return os;
}
