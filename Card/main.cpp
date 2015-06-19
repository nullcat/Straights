#include <iostream>
#include <cassert>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Command.h"
#include "Table.h"
#include "Game.h"

using namespace std;

const int NUM_PLAYERS = 4;

int main(int argc)
{
    Deck::seed = 44; //argc;   // set seed for random generator for shuffling

    Deck* deck = new Deck();
    Table* table = new Table();
    vector<Player*> players; //should be 4 players

    for(int i=0; i<NUM_PLAYERS;i++)
    {
        cout << "Is player " << (i+1) << " a human(h) or computer(c)?" << endl;

        char type;
        cin >> type;
        assert(type =='h' || type == 'c');

        if(type == 'h')
            players.push_back(new HumanPlayer());
        else if(type == 'c')
            players.push_back(new ComputerPlayer());
    }

    Game* game = new Game(players, *table, *deck);

    while(!game->hasEnded())
    {
        game->startNewRound();
    }

    delete deck;
    delete table;
    delete game;

    return 0;
}
