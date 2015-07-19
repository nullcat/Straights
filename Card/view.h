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
	Gtk::Button * cardFrames[4][13];

	//PlayerHand Widgets
	Gtk::Frame playerHandFrame;
	Gtk::HBox playerHandComponents;
	Gtk::Button * playerHandButton[13];
	Gtk::Image * playerHandCard[13];
    Gtk::Button rage_quit;


    //Message Dialog


	// Event handlers:
	void startButtonClicked();
	void resetButtonClicked();
	void playerHandCardClicked(int position);
	void statusButtonClicked(int position);
	void tabelCardButtonClicked(Card card);
	void ragequitButtonClicked();
	void autostartNewRound();

    //helper functions
    void updateTable(std::vector<Card>,std::vector<Card>,std::vector<Card>);
    void updatePlayerHand(std::vector<Card>,std::vector<Card>);
    void updateRound();
    void prepareNextRound();
    void initialize();
    void clearCards();
    void printResults();
    void printWinners();
    void updateScores();
    void endGame();


}; // View

#endif
