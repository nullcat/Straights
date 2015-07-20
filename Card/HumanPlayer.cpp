#include <iostream>

#include "HumanPlayer.h"
#include "Command.h"

using namespace std;


HumanPlayer::HumanPlayer(): Player() {}

void HumanPlayer::printHand() const
{
    cout << "Your hand: ";
    Player::printHand();
}
Type HumanPlayer::makeMove(Table& table, Deck& deck,Command c)
{
    getNewLegalPlays(table);

    cout << table;
    printHand();
    printLegalPlays();

    try
    {
        if (c.type == PLAY)
        {
            playCard(c.card, table);
            cout << "Player " << getPlayerNumber() << " plays " << c.card << "." << endl;
            return PLAY;
        }
        else if (c.type == DISCARD)
        {
            discardCard(c.card);
            cout << "Player " << getPlayerNumber() << " discards " << c.card << "." << endl;
            return DISCARD;
        }
        else if (c.type == DECK)
        {
            cout << deck << endl;
        }
        else if (c.type == QUIT)
        {
            return QUIT; //notifies Game class to quit, alternative would be to have IsHuman property, but that defeats the purpose of polymorphism
        }
        else if (c.type == RAGEQUIT)
        {
            return RAGEQUIT; //notifies Game class to ragequit this player, alternative would be to have IsHuman property, but that defeats the purpose of polymorphism
        }
        else if(c.type == BAD_COMMAND)
        {
            return BAD_COMMAND; //happens when player tries to make a move without input command
        }
    }
    catch(string invalidMoveMessage)
    {
        cout << invalidMoveMessage << endl;
        return BAD_COMMAND;
    }

}

