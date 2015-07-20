/*
 * View class.  Is responsible for displaying the game information
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

using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size,
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), panels(false), menu(false),start_button( "Start New Game with Seed:" ),rage_quit("I QUIT"), reset_button( "Quit Game" )
{

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
    reset_button.signal_clicked().connect(sigc::mem_fun(*this, &View::quitGameButtonClicked));

    // Add menu to the panel
    panels.add( menu );

    //initialize player info
    for(int i=0; i<4; i++)
    {


        playerScore[i].set_label("Score: 0");
        playerInfo[i].add(playerScore[i]);

        playerDiscards[i].set_label("Discards: 0");
        playerInfo[i].add(playerDiscards[i]);

        player_status[i].set_label("Human");
        player_status[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::playerStatusButtonClicked), i));
        playerInfo[i].add(player_status[i]);

        stringstream ss;
        ss<<"Player "<< (i+1);

        playerFrame[i].set_label(ss.str());

        playerFrame[i].add(playerInfo[i]);
        playersBox.add(playerFrame[i]);
    }
    panels.add(playersBox);

    //initialize instructions
    instrucFrame.set_label("Instructions");
    instrucLabel.set_alignment(0.5,0.5);
    instrucFrame.add(instrucLabel);
    panels.add(instrucFrame);

    //initialize table of cards
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<13; j++)
        {
            tableCard[i][j] = Gtk::manage(new Gtk::Image(deck.null()));
            tableCardButtons[i][j] = Gtk::manage(new Gtk::Button());
            tableCardButtons[i][j]->set_image(*tableCard[i][j]);
            tableCardButtons[i][j]->set_sensitive(false);
            Card card((Suit)i,(Rank)j);
            tableCardButtons[i][j]->signal_clicked().connect( sigc::bind<Card>( sigc::mem_fun(*this, &View::tabelCardButtonClicked), card));
            tableRow[i].add(*tableCardButtons[i][j]);
        }
        tableComponents.add(tableRow[i]);
    }
    table.set_label("Cards played:");
    table.add(tableComponents);
    panels.add(table);

    //initialize player hands
    for(int i=0; i<13; i++)
    {
        playerHandCard[i] = Gtk::manage(new Gtk::Image(deck.null()));
        playerHandButton[i] = Gtk::manage(new Gtk::Button());
        playerHandButton[i]->set_image(*playerHandCard[i]);
        playerHandButton[i]->set_sensitive(false);
        playerHandButton[i]->signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::playerHandCardClicked), i));
        playerHandComponents.add(*playerHandButton[i]);
    }
    rage_quit.signal_clicked().connect( sigc::mem_fun(*this, &View::ragequitButtonClicked));
    rage_quit.set_sensitive(false);

    playerHandComponents.add(rage_quit);
    playerHandFrame.set_label("Your hand");
    playerHandFrame.add(playerHandComponents);
    panels.add(playerHandFrame);

    // The final step is to display the buttons (they display themselves)
    show_all();

    // Register view as observer of model
    model_->subscribe(this);

} // View::View

View::~View() {}

//event handlers
void View::startButtonClicked()
{
    controller_->startNewGame(seed_input.get_text());
}
void View::quitGameButtonClicked()
{
    controller_->quitGame();
}
void View::playerStatusButtonClicked(int position)
{
    controller_->togglePlayer(position);
}
void View::playerHandCardClicked(int position)
{
    controller_->playOrDiscard(position);
}
void View::ragequitButtonClicked()
{
    controller_->rageQuit();
}
void View::autostartNewRound()
{
    controller_->startNewRound();
}
void View::tabelCardButtonClicked(Card card)
{
    vector<Card> hand = model_->getPlayerHand();
    for(int i=0; i<hand.size(); i++)
    {
        if(card == hand[i])
        {
            controller_->playOrDiscard(i);
            break;
        }
    }

}
void View::update()
{
    GameState state= model_->getState();
    switch(state)
    {
    case SETUP:
        initialize();
        break;
    case RUNNING:
        updateRound();
        break;
    case ROUND_END:
        prepareNextRound();
        break;
    case GAME_END:
        endGame();
        break;
    }
}

//view update functions
void View::initialize()
{
    clearCards();
    instrucLabel.set_label("");
    for(int i=0; i<4; i++)
    {

        player_status[i].set_sensitive(true);
        playerScore[i].set_label("Score: 0");
        playerDiscards[i].set_label("Discards: 0");
    }
    updatePlayerType(true);
    rage_quit.set_sensitive(false);
}

void View::updateRound()
{
    vector<int> discards = model_->getPlayerDiscards();
    vector<Card> tabelCards = model_->getTableCards();
    vector<Card> legalPlays = model_->getLegalPlays();
    vector<Card> playerHand = model_->getPlayerHand();
    int playerPosition = model_->getCurrentPlayerPosition();

    updateTable(tabelCards,legalPlays,playerHand);
    updatePlayerHand(playerHand,legalPlays);

    stringstream instrucstream;
    instrucstream<<"It's player "<<playerPosition<<"'s turn. ";
    if(legalPlays.size()==0)
    {
        instrucstream<<"You have no valid moves. Please choose a card to discard";
    }
    else
    {
        instrucstream<<"Please choose a card to play.";
    }
    instrucLabel.set_label(instrucstream.str());
    for(int i=0; i<4; i++)
    {
        stringstream discardstream;
        discardstream<<"Discards: "<<discards[i];
        playerDiscards[i].set_label(discardstream.str());

    }
    updatePlayerType(false);
}
void View::prepareNextRound()
{
    clearCards();
    updateScores();
    printResults();
    autostartNewRound(); //automatically start the next round
}
void View::endGame()
{
    updateScores();
    printResults();
    printWinners();
    quitGameButtonClicked(); //automatically resets the game
}

//helper functions
void View::printResults()
{
    Gtk::MessageDialog dialog(*this,model_->getResults());
    dialog.show_all_children();
    dialog.run();
    dialog.hide();
}
void View::printWinners()
{
    Gtk::MessageDialog dialog(*this,model_->getWinners());
    dialog.show_all_children();
    dialog.run();
    dialog.hide();

}
void View::updateScores()
{
    vector<int> discards = model_->getPlayerDiscards();
    vector<int> scores= model_->getPlayerScores();

    for(int i=0; i<4; i++)
    {
        stringstream scorestream;
        stringstream discardstream;

        scorestream<<"Score "<<scores[i];
        playerScore[i].set_label(scorestream.str());

        discardstream<<"Discards: "<<discards[i];
        playerDiscards[i].set_label(discardstream.str());
        player_status[i].set_sensitive(false);
    }
}

void View::updatePlayerType(bool sensitive)
{
    for(int i=0; i<4; i++)
    {
        if(model_->isHuman(i))
        {
            player_status[i].set_label("Human");
        }
        else
        {
            player_status[i].set_label("Computer");
        }
        player_status[i].set_sensitive(sensitive);
    }

}

void View::updateTable(vector<Card> tableCards, vector<Card> validCards,vector<Card> hand)
{
    //make all cards non-sensitive
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            tableCardButtons[i][j]->set_sensitive(false);
            tableCard[i][j]->set(deck.null());
        }
    }

    //set valid moves (if they are in your hand, sensitive)
    int length = tableCards.size();
    int valid_card_size = validCards.size();

    for(int i=0; i<valid_card_size; i++)
    {
        Card curCard = validCards[i];
        Rank r = curCard.getRank();
        Suit s = curCard.getSuit();

        if(find(hand.begin(),hand.end(),curCard)!=hand.end())
        {
            tableCard[s][r]->set(deck.valid_card());
            tableCardButtons[s][r]->set_sensitive(true);
        }
        else
        {
            tableCardButtons[s][r]->set_sensitive(false);
        }
    }

    //set cards on the table sensitive
    for(int i=0; i<length; i++)
    {
        Rank r = tableCards[i].getRank();
        Suit s = tableCards[i].getSuit();
        tableCard[s][r]->set(deck.image(r,s));

        tableCardButtons[s][r]->set_sensitive(true);
    }
}

void View::updatePlayerHand(vector<Card> hand,vector<Card> validCards)
{
    int hand_size = hand.size();
    int valid_card_size = validCards.size();

    //set valid moves in your card sensitive only
    for(int i=0; i<13; i++)
    {
        if(i<hand_size)
        {
            Card curCard = hand[i];
            playerHandCard[i] -> set(deck.image(curCard.getRank(),curCard.getSuit()));
            if(find(validCards.begin(),validCards.end(),curCard)!=validCards.end())
            {
                playerHandButton[i]->set_sensitive(true);
            }
            else
            {
                playerHandButton[i]->set_sensitive(false);
            }
            if(valid_card_size == 0)
            {
                playerHandButton[i]->set_sensitive(true);
            }
        }
        else
        {
            playerHandCard[i] -> set(deck.null());
            playerHandButton[i]->set_sensitive(false);
        }
        //playerHandButton[i]->set_sensitive(true);
        rage_quit.set_sensitive(true);
    }

}
void View::clearCards()
{
    for (int i = 0; i < 13; i++)
    {
        playerHandCard[i]->set(deck.null());
        playerHandButton[i]->set_sensitive(false);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            tableCard[i][j]->set(deck.null());
            tableCardButtons[i][j]->set_sensitive(false);
        }
    }
}
