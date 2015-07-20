#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "ComputerPlayer.h"

using namespace std;

bool ComputerPlayer::intelligentAI = false;

ComputerPlayer::ComputerPlayer() : Player() {}

ComputerPlayer::~ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(const Player& humanPlayer): Player(humanPlayer) {}

Type ComputerPlayer::makeMove(Table& table, Deck& deck, Command c)
{
    getNewLegalPlays(table);

    if(legalPlays_.empty())
    {
        if(ComputerPlayer::intelligentAI)
        {
            vector<Card> sortedHand = hand_;
            sort(sortedHand.begin(), sortedHand.end());

            cout << "Player " << getPlayerNumber() << " discards " << sortedHand[0] << "." << endl;
            discardCard(sortedHand[0]);
        }
        else
        {
            cout << "Player " << getPlayerNumber() << " discards " << hand_[0] << "." << endl;
            discardCard(hand_[0]);      //discard first card in hand
        }


        return DISCARD;
    }
    else
    {
        if(ComputerPlayer::intelligentAI)
        {
            cout << table;
            printHand();
            printLegalPlays();

            vector<Card> sortedHand = legalPlays_;
            sort(sortedHand.begin(), sortedHand.end());

            int suitRankCount[4];

            // get sum of ranks of each suit
            for(int i = 0; i < hand_.size(); i++)
            {
                suitRankCount[hand_[i].getSuit()] += hand_[i].getRank();
            }

            int highestSuitCount = suitRankCount[0];
            for(int i = 0; i < SUIT_COUNT; i++)
            {
                if(suitRankCount[i] > highestSuitCount)
                {
                    highestSuitCount = suitRankCount[i];
                }
            }

            //if the current sum of ranks is the highest for a 7 of the same suit, play the 7
            for(int i = 0; i < legalPlays_.size(); i++)
            {
                if(suitRankCount[legalPlays_[i].getSuit()]==highestSuitCount && legalPlays_[i].getRank()==7)
                {
                    cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[i] << "." << endl;
                    playCard(legalPlays_[i], table);    //play first legal card
                    return PLAY;
                }
            }

            // remove all bounded cards, we should avoid playing cards that will not benefit us in the future
            // i.e. avoid playing cards, that will not lead to another card
            if(!table.isEmpty())
            {
                int i = 0;
                while(i < sortedHand.size())
                {
                    if(sortedHand[i].getRank() != SEVEN)
                    {
                        bool isBound = true;

                        if(sortedHand[i].getRank() < SEVEN)
                        {
                            for(int j=0; j<hand_.size(); j++)
                            {
                                if(hand_[j] < sortedHand[i] && hand_[j].getSuit() == sortedHand[i].getSuit())
                                {
                                    isBound = false;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for(int j=0; j<hand_.size(); j++)
                            {
                                if(hand_[j] > sortedHand[i] && hand_[j].getSuit() == sortedHand[i].getSuit())
                                {
                                    isBound = false;
                                    break;
                                }
                            }
                        }

                        if(isBound)
                        {
                            sortedHand.erase(sortedHand.begin()+i);
                        }
                        else
                        {
                            i++;
                        }
                    }
                    else
                    {
                        sortedHand.erase(sortedHand.begin()+i);
                    }
                }
            }

            cout << "Recommended Cards: ";

            for(int i = 0; i<sortedHand.size(); i++)
            {
                cout << sortedHand[i] << " ";
            }

            cout << endl;

            if(!sortedHand.empty())
            {
                cout << "Player " << getPlayerNumber() << " plays " << sortedHand[sortedHand.size()-1] << "." << endl;
                playCard(sortedHand[sortedHand.size()-1], table);    //play first legal card
            }
            else
            {
                cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[legalPlays_.size()-1] << "." << endl;
                playCard(legalPlays_[legalPlays_.size()-1], table);    //play first legal card
            }
        }
        else
        {
            cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[0] << "." << endl;
            playCard(legalPlays_[0], table);    //play first legal card
        }

        return PLAY;
    }
}
