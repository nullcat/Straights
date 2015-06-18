#include <iostream>
#include <random>

#include "Deck.h"

Deck::Deck()
{
    for(int i = CLUB; i < SUIT_COUNT; i++)
    {
        for(int j = ACE; j < RANK_COUNT; j++)
        {
            cards_.push_back(Card((Suit)i, (Rank)j));
        }
    }
}

Deck::~Deck()
{
//    while(!cards_.empty())
//    {
//        Card *tmpCard = cards_.back();
//        cards_.pop_back();
//        delete tmpCard;
//    }
}

void Deck::shuffle()
{
    static mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		swap(cards_[n], cards_[k]);
	}
}

vector<Card> Deck::dealCards()
{
    vector<Card> cardsToPlayer;

    for(int i = deckDepth; i < DEAL_AMOUNT; i++)
    {
        cardsToPlayer.push_back(cards_[i]);
    }

    deckDepth += DEAL_AMOUNT;
//    vector<Card>::const_iterator first = cards_.begin();
//    vector<Card>::const_iterator last = cards_.begin() + DEAL_AMOUNT;
//
//    vector<Card> cardsToPlayer(first, last);
    return cardsToPlayer;
}

void Deck::printDeck() const
{
    for (int i = 0; i < cards_.size(); i++)
    {
        cout << cards_[i] << " ";

        // 13 per line
        if (i == 12 || i == 25 || i == 38 || i == 51)
        {
            cout << endl;
        }
    }

    cout << "\n>";
}
