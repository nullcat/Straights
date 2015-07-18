#include <ostream>
#include <istream>
#include <iostream>

#include "Game.h"
#include "Command.h"
#include "ComputerPlayer.h"

Game::Game(vector<Player*> players, Table& table, Deck& deck)
{
    players_ = players;
    deck_ = deck;
    table_ = table;
    endFlag_ = false;
    roundEndFlag_ = false;
}

Game::~Game(){}


vector<Card> Game::getPlayerHand() const{
    return currentPlayer_->getHand();
}

vector<Card> Game::getTableCards() const{
    return table_.getAllCards();
}

bool Game::gameEnded() const
{
    return endFlag_;
}
bool Game::roundEnded() const{
    return roundEndFlag_;
}
void Game::checkWinCondition()
{
    for(int i=0;i<players_.size();i++)
    {
        if(players_[i]->getScore() >= 80)
        {
            endFlag_ = true;
            printWinners();
            break;
        }
    }
}

void Game::printWinners() const
{
    int lowestScore = players_[0]->getScore();

    for(int i=1;i<players_.size();i++)
    {
        if(players_[i]->getScore() < lowestScore)
        {
            lowestScore = players_[i]->getScore();
        }
    }

    for(int i=0;i<players_.size();i++)
    {
        if(players_[i]->getScore() == lowestScore)
        {
            cout << "Player " << i+1 << " wins!" << endl;
        }
    }
}

void Game::printScores() const
{
    for(int i=0;i<players_.size();i++)
    {
        players_[i]->printDiscardsAndScore();
    }
}

int Game::getStarterPlayerNumber() const
{
    Card sevenSpade = Card(SPADE, SEVEN);

    for(int i=0;i<players_.size();i++)
    {
        if(players_[i]->hasCard(sevenSpade))
            return i;
    }

    throw string("incomplete or undealt deck");
}

void Game::dealDeck()
{
    for(int i=0; i<players_.size();i++)
    {
        players_[i]->addCards(deck_.dealCards());
    }
}

void Game::startNewRound()
{
    roundEndFlag_ = false;
    table_.clearTable();
    deck_.reset();
    deck_.shuffle();

    //reset players to prepare for new round
    for(int i = 0; i < players_.size(); i++)
        players_[i]->newRound();

    dealDeck();

    startingPlayerIndex_ = getStarterPlayerNumber();
    playerIndex_ = startingPlayerIndex_;
    currentPlayer_ = players_[playerIndex_];

    cout << "A new round begins. It's player " << startingPlayerIndex_+1 << "'s turn to play." << endl;

    Card dummy_card = Card(SUIT_COUNT,RANK_COUNT); //since we don't know which card to play or discard, we make this dummy card
    Type moveType = currentPlayer_->makeMove(table_, deck_, dummy_card);
    //either we need player input or the move is invalid, we pause this round
    if(moveType == BAD_COMMAND){
        return;
    }
    playRound();
}

void Game::resumeRound(int position){
    //TODO: workaround might write better code later
    Card card = Card(SUIT_COUNT,RANK_COUNT);

    if(position>=0){
        card = currentPlayer_->getHand()[position];
    }
    Type moveType = currentPlayer_->makeMove(table_, deck_, card);
    if(moveType == BAD_COMMAND){
        return;
    }
    if(moveType == QUIT)
    {
        endFlag_ = true;
        return;
    }


    playRound();


}

void Game::playRound(){
    Card dummy_card = Card(SUIT_COUNT,RANK_COUNT); //since we don't know which card to play or discard, we make this dummy card

    //the round ends when the player before the starting player has no cards
    while(players_[(startingPlayerIndex_+3)%4]->getHand().size()>0){
        nextPlayer(); //increment player
        Type moveType = currentPlayer_->makeMove(table_,deck_,dummy_card);

        //either we need player input or the move is invalid, we pause this round
        if(moveType == BAD_COMMAND){
            return;
        }
    }
    printScores();
    checkWinCondition();
    roundEndFlag_ = true;

//    //each round, each player loses 1 card, need to loop for number of cards of each player (the deal amount)
//    for(int rounds = 0; rounds < DEAL_AMOUNT; rounds++)
//    {
//        for(int i = 0; i < players_.size(); i++)
//        {
//            //start at the turn after the starter's turn
//            if(i == 0 && rounds == 0)
//                i = (starterIndex+1) % 4;
//
//            // if table is empty, end
//            if(table_.isEmpty())
//                break;
//
//            Type moveType = players_[i]->makeMove(table_, deck_);
//
//            if(moveType == QUIT)
//            {
//                endFlag_ = true;
//                return;
//            }
//            else if(moveType == RAGEQUIT)
//            {
//                players_[i] = convertToComputerPlayer(players_[i]);
//                cout << "Player " << i+1 << " ragequits. A computer will now take over." << endl;
//                players_[i]->makeMove(table_, deck_);   //computer makes a move
//            }
//        }
//    }
//
//    printScores();
//    checkWinCondition();
}

Player* Game::convertToComputerPlayer(Player* humanPlayer)
{
    Player* computerPlayer = new ComputerPlayer(*humanPlayer);
    delete humanPlayer;
    return computerPlayer;
}

void Game::nextPlayer(){
    playerIndex_ = playerIndex_ + 1;
    playerIndex_ = playerIndex_ % 4;
    currentPlayer_ = players_[playerIndex_];

}

vector<int> Game::getPlayerScores() const{
    vector<int> scores;
    for(int i=0;i<players_.size();i++){
        scores.push_back(players_[i]->getScore());
    }
    return scores;
}
vector<int> Game::getPlayerDiscards() const{
    vector<int> discards;
    for(int i=0;i<players_.size();i++){
        discards.push_back(players_[i]->getDiscards());
    }
    return discards;
}
int Game::ragequit(){

    currentPlayer_ = convertToComputerPlayer(currentPlayer_);
    players_[playerIndex_] = currentPlayer_;
    cout << "Player " << playerIndex_+1 << " ragequits. A computer will now take over." << endl;
    return playerIndex_;
}


