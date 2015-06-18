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

bool Table::isEmpty() const
{
    return cards_.empty();
}

void Table::printTable() const
{
    cout << "Cards on the table:" << endl;
    cout << "Clubs: ";
    printRanks(getCardsOfSuit(CLUB));
    cout << "Diamonds: ";
    printRanks(getCardsOfSuit(DIAMOND));
    cout << "Hearts: ";
    printRanks(getCardsOfSuit(HEART));
    cout << "Spades: ";
    printRanks(getCardsOfSuit(SPADE));
}

void Table::printRanks(vector<Card> cards) const
{
    for(int i=0;i<cards.size();i++)
    {
        cout << cards[i].getRank() << " ";
    }
}
