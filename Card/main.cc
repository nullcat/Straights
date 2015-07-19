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
#include <stdio.h>
using namespace std;

const int NUM_PLAYERS = 4;

int main(int argc, char* argv[])
{
    ComputerPlayer::intelligentAI = false;
    if(argc>1){
        if(string(argv[1])=="true" || string(argv[1])=="1" || string(argv[1])=="intelligent"){
            ComputerPlayer::intelligentAI = true;
        }
    }
    Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
	Model model;                          // Create model
    Controller controller( &model );  // Create controller
	View view( &controller, &model );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run( view );               // Show the window and return when it is closed.

    return 0;
}
