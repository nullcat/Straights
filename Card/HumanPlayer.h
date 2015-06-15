#ifndef _COMPUTERPLAYER_
#define _COMPUTERPLAYER_

#include <ostream>
#include <istream>

class HumanPlayer : public Player{
public:
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
private:
};

#endif
