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
    void startNewGame(std::string);
    void startNewRound();

    void makeMove(int position);
    void togglePlayer(int position);
    void quit();
    void ragequit();
    GameState getState() const;
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
    static bool intelligentAI;


private:
    Game * game_;
    bool isHuman_[4];
    GameState state_;
    void determineState();


}; // Model


#endif
