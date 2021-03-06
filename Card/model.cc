/*
 * MVC example of GTKmm program
 *
 * Model class.  Is responsible keeping track of the facade interface.
 * It knows nothing about views or controllers.
 */


#include "model.h"

using namespace std;

const int NUM_PLAYERS = 4;

Model::Model():state_(SETUP)
{
    for(int i=0; i<NUM_PLAYERS; i++)
    {
        isHuman_[i] = true;
    }
}

Model::~Model()
{

}
GameState Model::getState() const
{
    return state_;
}

bool Model::isHuman(int position) const
{
    return isHuman_[position];
}
vector<Card> Model::getTableCards() const
{
    return game_->getTableCards();
}
vector<Card> Model::getPlayerHand() const
{
    return game_->getPlayerHand();
}
vector<int> Model::getPlayerScores() const
{
    return game_->getPlayerScores();
}
vector<int> Model::getPlayerDiscards() const
{
    return game_->getPlayerDiscards();
}
string Model::getWinners() const
{
    if(state_ == GAME_END)
    {
        return game_->getWinners();
    }
    else
    {
        throw string("wrong state exception");
    }
}

string Model::getResults() const
{
    return game_->getResults();
}

void Model::startNewGame(string seed)
{

    Deck::seed = atoi(seed.c_str());
    Deck* deck = new Deck();
    Table* table = new Table();
    Player::NumberOfPlayers_ = 0;

    vector<Player*> players; //should be 4 players

    //cout<<*deck<<endl;
    for(int i=0; i<NUM_PLAYERS; i++)
    {
        if(isHuman_[i])
        {
            players.push_back(new HumanPlayer());
        }
        else
        {
            players.push_back(new ComputerPlayer());
        }
    }

    Game * game = new Game(players, *table, *deck);
    game_ = game;
    state_ = RUNNING;
    Deck::rng.seed(Deck::seed);
    startNewRound();

}
void Model::startNewRound()
{

    game_->startNewRound();
    determineState();
    notify();
}

void Model::playOrDiscard(int position)
{
    Command c;
    c.card = getPlayerHand()[position];

    vector<Card> legalPlays = getLegalPlays();
    if(legalPlays.size()>0)
    {
        c.type = PLAY;
    }
    else
    {
        c.type = DISCARD;
    }
    resumeGame(c);
}

void Model::quit()
{
    if(state_!=SETUP)
    {
        delete game_;
        state_ = SETUP;
        notify();
    }
}

void Model::ragequit()
{
    int index = game_->ragequit();
    isHuman_[index] = false;
    Command c;
    c.type= RAGEQUIT;
    notify();

    resumeGame(c);
}

void Model::resumeGame(Command c)
{
    game_->resumeRound(c);
    determineState();
    notify();
}

void Model::togglePlayer(int position)
{
    isHuman_[position] = !isHuman_[position];
    notify();
}
void Model::determineState()
{
    if(game_->gameEnded())
    {
        state_ = GAME_END;
    }
    else if(game_->roundEnded())
    {
        state_ = ROUND_END;
    }
    else
    {
        state_ = RUNNING;
    }
}
vector<Card> Model::getLegalPlays() const
{
    return game_->getLegalPlays();
}
int Model::getCurrentPlayerPosition() const
{
    return game_->getCurrentPlayerPosition();
}

