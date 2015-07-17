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


class Model : public Subject {
public:
    Model();
    virtual ~Model();
    void startNewGame(std::string);
    void startNewRound();
    std::vector<Card> getTableCards() const;
    std::vector<Card> getPlayerHand() const;


private:
    Game * game_;


}; // Model


#endif
