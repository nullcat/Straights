/*
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
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
   void playOrDiscard(int position);
private:
   Model *model_;
}; // Controller


#endif

