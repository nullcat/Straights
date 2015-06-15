#include <ostream>
#include <istream>
#include <random>

void Deck::shuffle(){
    static mt19937 rng(seed);

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = _cards[n];
		_cards[n] = _cards[k];
		_cards[k] = c;
	}
}
