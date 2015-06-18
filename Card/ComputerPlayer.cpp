#include <ostream>
#include <istream>

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() : Player()
{

}

ComputerPlayer::ComputerPlayer(const Player& humanPlayer)
{
    score_ = humanPlayer.getScore();
    hand_ = humanPlayer.getHand();
	discards_ = humanPlayer.getDiscards();
}

void ComputerPlayer::makeMove(Table& table)
{
    getNewLegalPlays(table);
    if(legalPlays_.empty())
        discardCard(hand_[0]); //discard first card in hand
    else
        playCard(legalPlays_.at(0), table);
}
