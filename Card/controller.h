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


#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H


#include <gtkmm.h>

class Model;

class Controller {
public:
   Controller( Model* );
   void startNewGame(std::string);
   void startNewRound();
   void quitGame();
   void rageQuit();
   void togglePlayer(int position);
   void makeMove(int position);
private:
   Model *model_;
}; // Controller


#endif

