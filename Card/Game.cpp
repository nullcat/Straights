#include <ostream>
#include <istream>
#include <iostream>
#include <sstream>
#include "Game.h"
#include "Command.h"
#include "ComputerPlayer.h"

using namespace std;

Game::Game(vector<Player*> players, Table& table, Deck& deck)
{
    players_ = players;
    deck_ = deck;
    table_ = table;
    endFlag_ = false;
    roundEndFlag_ = false;
}

Game::~Game() {}


vector<Card> Game::getPlayerHand() const
{
    return currentPlayer_->getHand();
}

vector<Card> Game::getTableCards() const
{
    return table_.getAllCards();
}

bool Game::gameEnded() const
{
    return endFlag_;
}
bool Game::roundEnded() const
{
    return roundEndFlag_;
}
void Game::checkWinCondition()
{
    for(int i=0; i<players_.size(); i++)
    {
        if(players_[i]->getScore() >= 80)
        {
            endFlag_ = true;
            printWinners();
            break;
        }
    }
}

string Game::getWinners() const
{
    stringstream ss;
    int lowestScore = players_[0]->getScore();
    for(int i=1; i<players_.size(); i++)
    {
        if(players_[i]->getScore() < lowestScore)
        {
            lowestScore = players_[i]->getScore();
        }
    }
    for(int i=0; i<players_.size(); i++)
    {
        if(players_[i]->getScore() == lowestScore)
        {
            ss << "Player " << i+1 << " wins!" << endl;
        }
    }
    return ss.str();
}

string Game::getResults() const
{
    stringstream ss;
    for(int i=0; i<players_.size(); i++)
    {
        ss << players_[i]->getDiscardsAndScore();
    }
    return ss.str();
}

void Game::printWinners() const
{
    cout<<getWinners();
}

void Game::printScores() const
{
    cout<<getResults();
}

void Game::setStartingPlayerNumber()
{
    Card sevenSpade = Card(SPADE, SEVEN);

    for(int i=0; i<players_.size(); i++)
    {
        if(players_[i]->hasCard(sevenSpade))
        {
            startingPlayerIndex_ = i;
            return;
        }
    }

    throw string("incomplete or undealt deck");
}

void Game::dealDeck()
{
    for(int i=0; i<players_.size(); i++)
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
    setStartingPlayerNumber();

    currentPlayer_ = players_[startingPlayerIndex_];

    cout << "A new round begins. It's player " << startingPlayerIndex_+1 << "'s turn to play." << endl;
    playRound();
}

//handles the play, discard, quit and ragequit commands
void Game::resumeRound(Command c)
{

    Type moveType = currentPlayer_->makeMove(table_, deck_, c);

    if(moveType == BAD_COMMAND)
    {
        return;
    }
    if(moveType == QUIT)
    {
        endFlag_ = true;
        return;
    }
    nextPlayer();
    playRound();
}

void Game::playRound()
{

    //the round ends when the player before the starting player has no cards
    while(currentPlayer_->getHand().size()>0)
    {

        //we don't know what the play input is,
        Command c;
        c.type = BAD_COMMAND;

        Type moveType = currentPlayer_->makeMove(table_,deck_,c);

        //either we need player input or the move is invalid, we pause this round
        if(moveType == BAD_COMMAND)
        {
            return;
        }
        nextPlayer(); //increment player
    }
    printScores();
    checkWinCondition();
    roundEndFlag_ = true;
}

Player* Game::convertToComputerPlayer(Player* humanPlayer)
{
    Player* computerPlayer = new ComputerPlayer(*humanPlayer);
    delete humanPlayer;
    return computerPlayer;
}

void Game::nextPlayer()
{
    int nextIndex = currentPlayer_->getPlayerNumber();
    nextIndex = nextIndex % 4;
    currentPlayer_ = players_[nextIndex];

}

vector<int> Game::getPlayerScores() const
{
    vector<int> scores;
    for(int i=0; i<players_.size(); i++)
    {
        scores.push_back(players_[i]->getScore());
    }
    return scores;
}
vector<int> Game::getPlayerDiscards() const
{
    vector<int> discards;
    for(int i=0; i<players_.size(); i++)
    {
        discards.push_back(players_[i]->getDiscards());
    }
    return discards;
}
int Game::ragequit()
{
    int index = currentPlayer_->getPlayerNumber() - 1;
    currentPlayer_ = convertToComputerPlayer(currentPlayer_);
    players_[index] = currentPlayer_;
    cout << "Player " << index+1 << " ragequits. A computer will now take over." << endl;
    return index;
}
//bonus features
vector<Card> Game::getLegalPlays() const
{
    return currentPlayer_->getLegalPlays();
}
int Game::getCurrentPlayerPosition() const
{
    return currentPlayer_->getPlayerNumber();
}


