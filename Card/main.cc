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
#include <gtkmm/main.h>
#include "model.h"
#include "controller.h"
#include "view.h"

using namespace std;

const int NUM_PLAYERS = 4;

int main(int argc, char* argv[])
{
    Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
	Model model;                          // Create model
        Controller controller( &model );  // Create controller
	View view( &controller, &model );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run( view );               // Show the window and return when it is closed.

//    Deck::seed = 0; //argc;   // set seed for random generator for shuffling
//		if(argc>1){
//			Deck::seed = atoi(argv[1]);
//		}
//    Deck* deck = new Deck();
//    Table* table = new Table();
//    vector<Player*> players; //should be 4 players
//
//    for(int i=0; i<NUM_PLAYERS;i++)
//    {
//        cout << "Is player " << (i+1) << " a human(h) or a computer(c)?" << endl;
//				cout <<">";
//        char type;
//        cin >> type;
//        assert(type =='h' || type == 'c');
//
//        if(type == 'h')
//            players.push_back(new HumanPlayer());
//        else if(type == 'c')
//            players.push_back(new ComputerPlayer());
//    }
//
//    Game* game = new Game(players, *table, *deck);
//
//    while(!game->hasEnded())
//    {
//        game->startNewRound();
//    }
//
//    delete deck;
//    delete table;
//    delete game;

    return 0;
}
