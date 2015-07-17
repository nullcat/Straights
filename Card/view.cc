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


#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include <iostream>
#include <sstream>

// Creates buttons with labels. Sets butBox elements to have the same size,
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), panels(false), menu(false), rage_quit("I QUIT!"),start_button( "Start New Game with Seed:" ), reset_button( "Restart Game" ) {

	// Sets some properties of the window.
    set_title( "CS247 Straights Card Game" );
	set_border_width( 10 );

	// Add panels to the window
	add(panels);

    seed_input.set_text("0");

    // Add componenets to the menu
	menu.add( start_button );
	menu.add(seed_input);
	menu.add( reset_button );

	start_button.signal_clicked().connect(sigc::mem_fun(*this, &View::startButtonClicked));

	// Add menu to the panel
	panels.add( menu );

    //initialize player info
    for(int i=0;i<4;i++){


      playerScore[i].set_label("Score: 0");
      playerInfo[i].add(playerScore[i]);

      playerDiscards[i].set_label("Discards: 0");
      playerInfo[i].add(playerDiscards[i]);

      player_status[i].set_label("Human");
      playerInfo[i].add(player_status[i]);

      std::stringstream ss;
      ss<<"Player "<< (i+1);

      playerFrame[i].set_label(ss.str());

      playerFrame[i].add(playerInfo[i]);
      playersBox.add(playerFrame[i]);
    }
    panels.add(playersBox);


    //initialize table of cards
    for(int i=0;i<4;i++){
      for(int j=0;j<13;j++){
        tableCard[i][j] = Gtk::manage(new Gtk::Image(deck.null()));
        cardFrames[i][j].add(*tableCard[i][j]);
        tableRow[i].add(cardFrames[i][j]);
      }
      tableComponents.add(tableRow[i]);
    }
    table.set_label("Cards played:");
    table.add(tableComponents);
    panels.add(table);

    //initialize player hands
    for(int i=0;i<13;i++){
      playerHandCard[i] = Gtk::manage(new Gtk::Image(deck.null()));
      playerHandFrames[i].add(*playerHandCard[i]);
      playerHandComponents.add(playerHandFrames[i]);
    }
    playerHandComponents.add(rage_quit);
    playerHand.set_label("Your hand");
    playerHand.add(playerHandComponents);
    panels.add(playerHand);


	//reset_button.signal_clicked().connect( sigc::mem_fun( *this, &View::resetButtonClicked ) );


	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {
    updateTable(model_->getTableCards());
    updatePlayerHand(model_->getPlayerHand());
  //Suits suit = model_->suit();
  //Faces face = model_->face();
  //if ( suit == NOSUIT )
  //  card.set( deck.null() );
  //else
  // card.set( deck.image(face, suit) );

}

void View::startButtonClicked() {
  controller_->startNewGame(seed_input.get_text());
} // View::nextButtonClicked

void View::resetButtonClicked() {
  controller_->resetButtonClicked();
} // View::resetButtonClicked

void View::updateTable(vector<Card> tableCards){

}

void View::updatePlayerHand(vector<Card> hand){
    int hand_size = hand.size();
    for(int i=0;i<13;i++){
      Card curCard = hand[i];
      if(i<hand_size){
        playerHandCard[i] -> set(deck.image(curCard.getRank(),curCard.getSuit()));
      }
      else{
        playerHandCard[i] -> set(deck.null());
      }
    }
}
