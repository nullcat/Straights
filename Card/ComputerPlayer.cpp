#include <ostream>
#include <istream>
#include <iostream>

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() : Player(){}

ComputerPlayer::~ComputerPlayer(){}

ComputerPlayer::ComputerPlayer(const Player& humanPlayer): Player(humanPlayer){}

Type ComputerPlayer::makeMove(Table& table, Deck& deck)
{
    getNewLegalPlays(table);
    if(legalPlays_.empty())
    {
        discardCard(hand_[0]); //discard first card in hand
        cout << "Player " << getPlayerNumber() << " discards " << hand_[0] << endl;
        return DISCARD;
    }
    else
    {
        playCard(legalPlays_[0], table);
        cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[0] << endl;
        return PLAY;
    }
}
