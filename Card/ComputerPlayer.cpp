#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ComputerPlayer.h"

bool ComputerPlayer::intelligentAI = false;

ComputerPlayer::ComputerPlayer() : Player(){}
ComputerPlayer::~ComputerPlayer(){}
ComputerPlayer::ComputerPlayer(const Player& humanPlayer): Player(humanPlayer){}
Type ComputerPlayer::makeMove(Table& table, Deck& deck,Card card)
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
    //        cout << table;
    //        printHand();
    //        printLegalPlays();
            vector<Card> sortedHand = legalPlays_;
            sort(sortedHand.begin(), sortedHand.end());
            int suitCount[4];
            for(int i = 0; i < hand_.size(); i++)
            {
                suitCount[hand_[i].getSuit()]++;
            }
            Suit dominantSuit = CLUB;
            int highestSuitCount = suitCount[0];
            for(int i = 1; i < SUIT_COUNT; i++)
            {
                if(suitCount[i] > highestSuitCount)
                {
                    highestSuitCount = suitCount[i];
                    dominantSuit = (Suit)(i);
                }
            }
            for(int i = 0; i < legalPlays_.size(); i++)
            {
                if(legalPlays_[i].getSuit()==dominantSuit && legalPlays_[i].getRank()==7)
                {
                    cout << "Player " << getPlayerNumber() << " plays " << legalPlays_[i] << "." << endl;
                    playCard(legalPlays_[i], table);    //play first legal card
                    return PLAY;
                }
            }
            if(!table.isEmpty())
            {
                int i = 0;
                while(i < sortedHand.size())
                {
                    vector<Card> suitCards = table.getCardsOfSuit(sortedHand[i].getSuit());
                    if(suitCards.empty())
                        break;
                    Card upperBound = suitCards[suitCards.size()-1];
                    Card lowerBound = suitCards[0];
                    if((sortedHand[i] == upperBound || sortedHand[i] > upperBound) || (sortedHand[i] == lowerBound || sortedHand[i] < lowerBound))
                        sortedHand.erase(sortedHand.begin()+i);
                    i++;
                }
            }
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
