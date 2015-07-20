/*
 * MVC example of GTKmm program
 *
 * Model class.  Is responsible keeping track of the deck of cards.
 * It knows nothing about views or controllers.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef MVC_MODEL_H
#define MVC_MODEL_H

#include "subject.h"
#include "Game.h"
#include "Card.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>

enum GameState{SETUP,RUNNING,ROUND_END,GAME_END};

class Model : public Subject {
public:
    Model();
    virtual ~Model();
    void startNewGame(std::string);             //initialize game using seed
    void startNewRound();                       //intialize round
    void playOrDiscard(int position);                //determine what move to make from user input
    void togglePlayer(int position);            //change the human player to computer player at the SETUP state
    void quit();                                //destruct the game
    void ragequit();                            //change the human player to computer player when game is running
    GameState getState() const;                 //get state of model

    //accessors
    bool isHuman(int position) const;
    std::vector<Card> getTableCards() const;
    std::vector<Card> getPlayerHand() const;
    std::vector<bool> getPlayerType() const;
    std::vector<int> getPlayerScores() const;
    std::vector<int> getPlayerDiscards() const;
    std::string getWinners() const;
    std::string getResults() const;
    std::vector<Card> getLegalPlays() const;
    int getCurrentPlayerPosition() const;
private:
    Game * game_;                               //facade game object to interact with model
    bool isHuman_[4];                           //boolean array of the type of the 4 players (0 = computer, 1 = human)
    GameState state_;                           //the current stage of the game

    void determineState();                      //determine the current state of game after each move
    void resumeGame(Command c);                 //resume game with command from input


}; // Model


#endif
