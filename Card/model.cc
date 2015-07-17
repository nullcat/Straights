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


#include "model.h"

using namespace std;

const int NUM_PLAYERS = 4;

Model::Model() {}

Model::~Model(){

}

vector<Card> Model::getTableCards() const{
    return game_->getTableCards();
}

vector<Card> Model::getPlayerHand() const{
    return game_->getPlayerHand();
}

void Model::startNewGame(string seed){

    //if(game_){
    //    delete game_;
    //}
    Deck::seed = atoi(seed.c_str());
    Deck* deck = new Deck();
    Table* table = new Table();
    vector<Player*> players; //should be 4 players
    //cout<<*deck<<endl;
    for(int i=0; i<NUM_PLAYERS;i++)
    {
        players.push_back(new HumanPlayer());
    }

    Game * game = new Game(players, *table, *deck);
    game_ = game;
    startNewRound();
    //delete deck;
    //delete table;
    //delete game;

}
void Model::startNewRound(){
    game_->startNewRound();
    notify();
}
