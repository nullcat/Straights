#ifndef _PLAYER_
#define _PLAYER_

#include <ostream>
#include <istream>

enum Type {HUMAN, PLAYER};

class Player{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
private:
	string _name;
};

bool operator==(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
