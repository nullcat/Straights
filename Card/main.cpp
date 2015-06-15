#include <iostream>

using namespace std;

int main()
{
    Player* players = new Player[4]; //should always be 4 players

    for(int i=0; i<4;i++)
    {
        cout << "Is player <x> a human(h) or computer(c)" << endl;

        char type;
        cin >> type;
        if(type == 'h')
            players[i] = new HumanPlayer();
        else
            players[i] = new ComputerPlayer();
    }

    cout << "Is player <x> a human(h) or computer(c)"
    return 0;
}
