#include "Player.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>

using namespace std;

// initializes static player count to zero
int Player::NumberOfPlayers_ = 0;

Player::Player(): score_(0), oldScore_(0), playerNumber_(++NumberOfPlayers_) {}

Player::Player(const Player& otherPlayer)
{
    score_ = otherPlayer.getScore();
    oldScore_ = otherPlayer.getOldScore();
    playerNumber_ = otherPlayer.getPlayerNumber();
    hand_ = otherPlayer.hand_;
    discards_ = otherPlayer.discards_;
}

Player::~Player() {}

void Player::addCards(vector<Card> cards)
{
    for(int i=0; i<cards.size(); i++)
    {
        hand_.push_back(cards[i]);
    }
}

void Player::newRound()
{
    hand_.clear();
    discards_.clear();

    oldScore_ = score_;
}

void Player::printHand() const
{
    printCards(hand_);
}

void Player::printLegalPlays() const
{
    cout << "Legal plays: ";
    printCards(legalPlays_);
}

void Player::printDiscardsAndScore() const
{
    cout<<getDiscardsAndScore();
}


string Player::getDiscardsAndScore() const
{
    stringstream ss;
    ss << "Player " << getPlayerNumber() << "'s discards: "
       <<getCards(discards_)
       << "Player " << getPlayerNumber() << "'s score: " << getOldScore() << " + " << getScore()-getOldScore() << " = " << getScore() << endl;
    return ss.str();
}

void Player::printCards(vector<Card> cards) const
{
    cout<<getCards(cards);
}
string Player::getCards(vector<Card> cards) const
{
    stringstream ss;
    for(int i = 0; i < cards.size(); i++)
    {
        ss << cards[i];

        if(i != cards.size()-1)
            ss << " ";
    }

    ss << endl;
    return ss.str();
}

int Player::getScore() const
{
    return score_;
}

int Player::getOldScore() const
{
    return oldScore_;
}

int Player::getPlayerNumber() const
{
    return playerNumber_;
}

int Player::getDiscards() const
{
    return discards_.size();
}

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
vector<Card> Player::getHand() const
{
    return hand_;
}

vector <Card> Player::getLegalPlays() const
{
    return legalPlays_;
}

void Player::playCard(Card card, Table& table)
{
    for(int i = 0; i < legalPlays_.size(); i++)
    {
        if(legalPlays_[i] == card)
        {
            table.addCard(card);
            removeCard(card);
            return;
        }
    }

    throw string("This is not a legal play.");
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
        throw string("You have a legal play. You may not discard.");

    discards_.push_back(card);
    score_ += card.getRank() + 1;   // score only goes up on discarding a card
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
    legalPlays_.clear();

    if(table.isEmpty() == true)
    {
        Card sevenSpade = Card(SPADE, SEVEN);

        if(hasCard(sevenSpade))
            legalPlays_.push_back(sevenSpade);
    }
    else
    {
        for(int i = 0; i < hand_.size(); i++)
        {
            Card curCard = hand_[i];
            Suit curSuit = curCard.getSuit();
            Rank curRank = curCard.getRank();

            if(curRank == SEVEN)
                legalPlays_.push_back(curCard);
            else
            {
                vector<Card> sameSuitCards = table.getCardsOfSuit(curSuit);

                for(int j=0; j<sameSuitCards.size(); j++)
                {
                    // note that it should be impossible to have same suit and rank (same card)
                    if(abs((int)curRank - (int)sameSuitCards[j].getRank()) <= 1) //1 or -1 difference in rank, 0 is not possible unless they were the same card
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
