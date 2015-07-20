/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "controller.h"
#include "model.h"

using namespace std;

Controller::Controller(Model *m) : model_(m) {}

//tell the model to start new game
void Controller::startNewGame(string seed)
{
    model_->startNewGame(seed);
}
//instruct model to start new round
void Controller::startNewRound()
{
    model_->startNewRound();
}
//instruct the model to change the type of player (eg human->computer)
void Controller::togglePlayer(int position)
{
    model_->togglePlayer(position);
}
//instruct the model to play or discard the current player's hand
void Controller::playOrDiscard(int position)
{
    model_->playOrDiscard(position);
}
//insturct the model to convert the current player into computer and then make a move
void Controller::rageQuit()
{
    model_->ragequit();
}
//instruct the model to terminate the current game
void Controller::quitGame()
{
    model_->quit();
}
