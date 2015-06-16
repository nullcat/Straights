#include <ostream>
#include <istream>
#include <random>

#include "Deck.h"

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
    if(cards_.empty())
        throw "error, no cards in the deck.";

    vector<Card>::const_iterator first = cards_.begin();
    vector<Card>::const_iterator last = cards_.begin() + DEAL_AMOUNT;

    vector<Card> cardsToPlayer(first, last);
    return cardsToPlayer;
}
