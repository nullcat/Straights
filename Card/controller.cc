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


void Controller::startNewGame(string seed) {
     model_->startNewGame(seed);
}
void Controller::startNewRound() {
     model_->startNewRound();
}

void Controller::togglePlayer(int position){
    model_->togglePlayer(position);
}
void Controller::makeMove(int position){
    model_->makeMove(position);
}
void Controller::quitGame(){
    model_->quit();
}
void Controller::rageQuit(){
    model_->makeMove(-1);
}
