/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "observer.h"
#include "algorithm"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
        View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;

	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

    Gtk::VBox panels;      // Main window divided into two horizontal panels
	Gtk::HBox menu;      // Vertical boxes for stacking buttons vertically

    //Menu Buttons
	Gtk::Button start_button;
	Gtk::Entry seed_input;
	Gtk::Button reset_button;

    //PlayerInfo widgest
    Gtk::HBox playersBox;
    Gtk::Frame playerFrame[4];
    Gtk::VBox playerInfo[4];
    Gtk::Label playerScore[4];
    Gtk::Label playerDiscards[4];
    Gtk::Button player_status[4];

    //Instructions widgets
    Gtk::Frame instrucFrame;
    Gtk::Label instrucLabel;

	//Table card widgets
	Gtk::Frame table;
	Gtk::VBox tableComponents;
	Gtk::HBox tableRow[4];

	Gtk::Image * tableCard[4][13];
	Gtk::Button * tableCardButtons[4][13];

	//PlayerHand Widgets
	Gtk::Frame playerHandFrame;
	Gtk::HBox playerHandComponents;
	Gtk::Button * playerHandButton[13];
	Gtk::Image * playerHandCard[13];
    Gtk::Button rage_quit;


	// Event handlers:
	void startButtonClicked();                                                  //forward start new game button event to controller
	void quitGameButtonClicked();                                               //forward quit game button event to controller
    void playerHandCardClicked(int position);                                   //forward playing a card from hand event to controller
	void playerStatusButtonClicked(int position);                               //forward changing the status (human or computer) to controller
	void tabelCardButtonClicked(Card card);                                     //forward playing a card from table event to controller
	void ragequitButtonClicked();                                               //forward clicking the ragequit button to controller
	void autostartNewRound();                                                   //tells controller to start a new round

    //main update functions
    void initialize();                                                          //when model is in state SETUP
    void updateRound();                                                         //when model is in state RUNNING
    void prepareNextRound();                                                    //when model is in state ROUND_END
    void endGame();                                                             //when model is in state GAME_END

    //helper functions
    void updateTable(std::vector<Card>,std::vector<Card>,std::vector<Card>);   //update table with information on valid moves, and table cards
    void updatePlayerHand(std::vector<Card>,std::vector<Card>);                //update player hand with information on valid moves
    void clearCards();
    void printResults();
    void printWinners();
    void updateScores();
    void updatePlayerType(bool);                                                //update the player/computer buttons, true to allow interaction

}; // View

#endif
