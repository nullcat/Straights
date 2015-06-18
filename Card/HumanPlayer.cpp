#include <iostream>

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(): Player() {}

void HumanPlayer::printHand() const
{
    cout << "Your hand: ";
    Player::printHand();
}

void HumanPlayer::makeMove(Table &table)
{

}
