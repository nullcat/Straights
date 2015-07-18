#include <ostream>
#include <istream>
#include <iostream>

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() : Player(){}

ComputerPlayer::~ComputerPlayer(){}

ComputerPlayer::ComputerPlayer(const Player& humanPlayer): Player(humanPlayer){}

Type ComputerPlayer::makeMove(Table& table, Deck& deck,Card card)
{
    getNewLegalPlays(table);
    if(legalPlays_.empty())
    {
        cout << "Player " << getPlayerNumber() << " discards " << hand_[0] << "." << endl;
        discardCard(hand_[0]);      //discard first card in hand
        return DISCARD;
    }
    else
    {
        cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[0] << "." << endl;
        playCard(legalPlays_[0], table);    //play first legal card
        return PLAY;
    }
}
