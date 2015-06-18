#include "Player.h"

#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

Player::Player()
{
    score_ = 0;
}

Player::~Player(){}

void Player::printHand() const
{
	for(int i = 0; i < hand_.size(); i++)
    {
        cout << hand_[i] << endl;
    }
}

void Player::printLegalPlays() const
{
	for(int i = 0; i < hand_.size(); i++)
    {
        cout << legalPlays_[i] << endl;
    }
}

int Player::getScore() const
{
    return score_;
}

Card Player::findCard(Card card) const
{
}

bool Player::hasCard(Card card) const
{
    for(int i = 0; i < hand_.size(); i++)
    {
        if(hand_[i] == hand_[i])
        {
            return true;
        }
    }

    return false;
}

void Player::discardCard(Card card)
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
        throw "You have a legal play. You may not discard.";

    discards_.push_back(card);
    score_ += card.getRank();
    removeCard(card);
}

void Player::removeCard(Card card)
{
    for(vector<Card>::iterator i = hand_.begin(); i != hand_.end(); i++)
    {
        if(*i == card)
        {
            hand_.erase(i);
            return;
        }
    }

    // else nothing happens
}

void Player::getNewLegalPlays(vector<Card> tableCards)
{
    if(tableCards.empty())
    {
        Card sevenSpade = Card(SPADE, SEVEN);

        if(hasCard(sevenSpade))
        {
            legalPlays_.clear();
            legalPlays_.push_back(sevenSpade);
        }
    }
    else
    {
        for(int i; i < hand_.size(); i++)
        {
            Card curCard = hand_[i];
            Suit curSuit = curCard.getSuit();
            Rank curRank = curCard.getRank();

            if(curRank == SEVEN)
                legalPlays_.push_back(curCard);
            else
            {

            }
        }
    }
}
