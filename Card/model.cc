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

Model::Model():gameStarted_(false) {
    for(int i=0;i<NUM_PLAYERS;i++){
        isHuman_[i] = true;
    }
}

Model::~Model(){

}
bool Model::gameStarted() const{
    return gameStarted_;
}
bool Model::roundOver() const{
    return game_->roundEnded();
}
bool Model::gameOver() const{
    return game_->gameEnded();
}

bool Model::isHuman(int position) const{
    return isHuman_[position];
}
vector<Card> Model::getTableCards() const{
    return game_->getTableCards();
}
vector<Card> Model::getPlayerHand() const{
    return game_->getPlayerHand();
}
vector<int> Model::getPlayerScores() const{
    return game_->getPlayerScores();
}
vector<int> Model::getPlayerDiscards() const{
    return game_->getPlayerDiscards();
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
        if(isHuman_[i]){
            players.push_back(new HumanPlayer());
        }
        else{
            players.push_back(new ComputerPlayer());
        }
    }

    Game * game = new Game(players, *table, *deck);
    game_ = game;
    gameStarted_ = true;

    startNewRound();
    //delete deck;
    //delete table;
    //delete game;

}
void Model::startNewRound(){

    game_->startNewRound();
    if(game_->gameEnded()){
        gameStarted_ = false;
    }
    notify();
}

void Model::makeMove(int position){

    if(position == -1){
        int index = game_->ragequit();
        isHuman_[index] = false;
    }
    game_->resumeRound(position);
    if(game_->gameEnded()){
        gameStarted_ = false;
    }
    notify();
}
void Model::quit(){
    if(gameStarted_){
        delete game;
        gameStarted_ = false;
        notify();
    }
}
void Model::ragequit(){
    game_->ragequit();
}

void Model::togglePlayer(int position){
    isHuman_[position] = !isHuman_[position];
    notify();
}

