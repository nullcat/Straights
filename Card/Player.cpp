#include "Player.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>

using namespace std;

Player::Player(): score_(0){}

Player::~Player(){}

void Player::printHand() const
{
	printCards(hand_);
}

void Player::printLegalPlays() const
{
    cout << "Legal plays: ";
	printCards(legalPlays_);
}

void Player::printCards(vector<Card> cards) const
{
    for(int i = 0; i < hand_.size(); i++)
    {
        cout << legalPlays_[i] << " ";
    }

    cout << endl;
}

vector<Card> Player::getHand() const
{
    return hand_;
}

vector<Card> Player::getDiscards() const
{
    return discards_;
}

int Player::getScore() const
{
    return score_;
}

//Card Player::findCard(Card card) const
//{
//}

bool Player::hasCard(Card card) const
{
    for(int i = 0; i < hand_.size(); i++)
    {
        if(hand_[i] == card)
        {
            return true;
        }
    }

    return false;
}

void Player::playCard(Card card, Table& table)
{
    for(int i = 0; i < legalPlays_.size(); i++)
    {
        if(legalPlays_[i] == card)
        {
            table.addCard(card);
            removeCard(card);
        }
    }

    throw "This is not a legal play.";
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

void Player::getNewLegalPlays(const Table &table)
{
    if(table.isEmpty())
    {
        Card sevenSpade = Card(SPADE, SEVEN);

        if(hasCard(sevenSpade))
        {
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
                vector<Card> sameSuitCards = table.getCardsOfSuit(curSuit);

                for(int j=0;j<sameSuitCards.size();j++)
                {
                    // note that it should be impossible to have same suit and rank (same card)
                    if(abs(curRank - sameSuitCards[j].getRank()) <= 1) //1 or -1 difference in rank, 0 is not possible unless they were the same card
                    {
                        legalPlays_.push_back(curCard);
                        break;
                    }
                }
            }
        }
    }
}

bool Player::IsLegalPlay(Card card)
{
    for(int i = 0; i < legalPlays_.size(); i++)
    {
        if(legalPlays_[i] == card)
        {
            return true;
        }
    }

    return false;
}
