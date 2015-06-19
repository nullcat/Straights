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
}

Game::~Game(){}

bool Game::hasEnded() const
{
    return endFlag_;
}

void Game::checkWinCondition()
{
    for(int i=0;i<players_.size();i++)
    {
        if(players_[i]->getScore() >= 80)
        {
            endFlag_ = true;
            cout << "Player " << i+1 << " wins!";
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

    throw "incomplete or undealt deck";
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
    table_.clearTable();
    deck_.reset();
    deck_.shuffle();

    // reset players to prepare for new round
    for(int i = 0; i < players_.size(); i++)
        players_[i]->newRound();

    dealDeck();

    int starterIndex = getStarterPlayerNumber();

    cout << "A new round begins. It's player " << starterIndex+1 << "'s turn to play." << endl;

    players_[starterIndex]->makeMove(table_, deck_);

    for(int rounds = 0; rounds < DEAL_AMOUNT; rounds++)
    {
        for(int i = 0; i < players_.size(); i++)
        {
            Type moveType = players_[i]->makeMove(table_, deck_);

            if(moveType == QUIT)
            {
                endFlag_ = true;
                return;
            }
            else if(moveType == RAGEQUIT)
            {
                players_[i] = convertToComputerPlayer(players_[i]);
                players_[i]->makeMove(table_, deck_);
                cout << "Player " << i+1 << " ragequits. A computer will now take over.";
            }
        }
    }

    printScores();
    checkWinCondition();
}

Player* Game::convertToComputerPlayer(Player* humanPlayer)
{
    Player* computerPlayer = new ComputerPlayer(*humanPlayer);
    delete humanPlayer;
    return computerPlayer;
}
