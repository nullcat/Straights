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
View::View(Controller *c, Model *m) : model_(m), controller_(c), panels(false), menu(false),start_button( "Start New Game with Seed:" ),rage_quit("I QUIT"), reset_button( "Restart Game" ) {

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
    reset_button.signal_clicked().connect(sigc::mem_fun(*this, &View::resetButtonClicked));

	// Add menu to the panel
	panels.add( menu );

    //initialize player info
    for(int i=0;i<4;i++){


      playerScore[i].set_label("Score: 0");
      playerInfo[i].add(playerScore[i]);

      playerDiscards[i].set_label("Discards: 0");
      playerInfo[i].add(playerDiscards[i]);

      player_status[i].set_label("Human");
      player_status[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::statusButtonClicked), i));
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
      playerHandButton[i] = Gtk::manage(new Gtk::Button());
      playerHandButton[i]->set_image(*playerHandCard[i]);
      playerHandButton[i]->set_sensitive(false);
      playerHandButton[i]->signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::playerHandCardClicked), i));
      playerHandComponents.add(*playerHandButton[i]);
    }
    rage_quit.signal_clicked().connect( sigc::mem_fun(*this, &View::ragequitButtonClicked));
    rage_quit.set_sensitive(false);
    //player_status[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::statusButtonClicked), i));
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

//event handlers
void View::startButtonClicked() {
  controller_->startNewGame(seed_input.get_text());
} // View::nextButtonClicked

void View::resetButtonClicked() {
  controller_->quitGame();
} // View::resetButtonClicked
void View::statusButtonClicked(int position){
    controller_->togglePlayer(position);
}
void View::playerHandCardClicked(int position){
  controller_->makeMove(position);
}
void View::ragequitButtonClicked(){
  controller_->rageQuit();
}
void View::autostartNewRound(){
  controller_->startNewRound();
}


void View::update() {
    if(model_->gameStarted()){
        if(model_->roundOver()){
            prepareNextRound();
        }
        else{
            updateRound();
        }
    }
    else{
        initialize();
    }
}


void View::initialize(){
    for(int i=0;i<4;i++){
      clearCards();
      player_status[i].set_sensitive(true);
      playerScore[i].set_label("Score: 0");
      playerDiscards[i].set_label("Discards: 0");

      if(model_->isHuman(i)){
        player_status[i].set_label("Human");
      }
      else{
        player_status[i].set_label("Computer");
      }
    }
    rage_quit.set_sensitive(false);
}

void View::updateRound(){
    updateTable(model_->getTableCards());
    updatePlayerHand(model_->getPlayerHand());

    vector<int> discards = model_->getPlayerDiscards();

    for(int i=0;i<4;i++){
      stringstream discardstream;
      discardstream<<"Discards: "<<discards[i];
      playerDiscards[i].set_label(discardstream.str());
      if(model_->isHuman(i)){
        player_status[i].set_label("Human");
      }
      else{
        player_status[i].set_label("Computer");
      }
      player_status[i].set_sensitive(false);
    }
}
void View::prepareNextRound(){

    clearCards();
    vector<int> discards = model_->getPlayerDiscards();
    vector<int> scores= model_->getPlayerScores();

    for(int i=0;i<4;i++){
      stringstream scorestream;
      stringstream discardstream;

      scorestream<<"Score "<<scores[i];
      playerScore[i].set_label(scorestream.str());

      discardstream<<"Discards: "<<discards[i];
      playerDiscards[i].set_label(discardstream.str());
    }
    autostartNewRound(); //start the next round automatically
}



void View::updateTable(vector<Card> tableCards){
    int length = tableCards.size();
    for(int i=0;i<length;i++){
        Rank r = tableCards[i].getRank();
        Suit s = tableCards[i].getSuit();
        tableCard[s][r]->set(deck.image(r,s));
    }
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
      playerHandButton[i]->set_sensitive(true);
      rage_quit.set_sensitive(true);
    }
}
void View::clearCards(){
    for (int i = 0; i < 13; i++) {
		playerHandCard[i]->set(deck.null());
		playerHandButton[i]->set_sensitive(false);
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			tableCard[i][j]->set(deck.null());
		}
	}
}
