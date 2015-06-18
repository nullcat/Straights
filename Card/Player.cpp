#include "Player.h"

#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

void Player::printHand() const
{
	for(int i = 0; i < hand_.size(); i++)
    {
        cout << *hand_[i] << endl;
    }
}

void Player::printLegalPlays() const
{
	for(int i = 0; i < hand_.size(); i++)
    {
        cout << *legalPlays_[i] << endl;
    }
}

int Player::getScore() const
{
    return score_;
}

Card* Player::findCard(Suit suit, Rank rank) const
{
    for(int i = 0; i < hand_.size(); i++)
    {
        if(hand_.at(i)->getSuit() == suit && hand_.at(i)->getRank() == rank)
        {
            return hand_.at(i);
        }
    }

    return NULL;
}

bool Player::hasCard(Suit suit, Rank rank) const
{
    for(int i = 0; i < hand_.size(); i++)
    {
        if(hand_.at(i)->getSuit() == suit && hand_.at(i)->getRank() == rank)
        {
            return true;
        }
    }

    return false;
}

void Player::discardCard(Card* card)
{
    bool isLegal = false;

    for(int i = 0; i < hand_.size(); i++)
    {
        if(IsLegalPlay(hand_[i]))
        {
            isLegal = true;
            break;
        }
    }

    if(isLegal)
        throw string("You have a legal play. You may not discard.");

    discards_.push_back(card);
    score_ += card->getRank();
}

void Player::removeCard(Card* card)
{
    for(int i = )
}

void Player::getNewLegalPlays(vector<Card*> tableCards)
{
    if(tableCards.empty())
    {
        Card* sevenSpade = findCard(SPADE, SEVEN);

        if(sevenSpade != NULL)
        {
            legalPlays_.clear();
            legalPlays_.push_back(sevenSpade);
        }
    }
}
