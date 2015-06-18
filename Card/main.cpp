#include <iostream>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Command.h"
#include "Table.h"

using namespace std;

const int NUM_PLAYERS(4);

int main(int argc, char* argv[])
{
    Deck::seed = argc;   // set seed for random generator for shuffling

    Deck* _deck = new Deck();
    Table* _table = new Table();
    Player* _players = new Player[NUM_PLAYERS]; //should be 4 players

    for(int i=0; i<4;i++)
    {
        cout << "Is player <x> a human(h) or computer(c)" << endl;

        char type;
        cin >> type;
        if(type == 'h');
            //_players[i] = new HumanPlayer();
        //else
            //_players[i] = new ComputerPlayer();
    }



    cout << "A new round begins. It's player 4's turn to play." << endl;

    //Command _command = new Command();
    //_command.type = Type.BAD_COMMAND

    return 0;
}
