#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

using std::cout;
using std::endl;
using std::string;



int main(void) 
{
    Game game;
    
    cout << YELLOW << BOLD << "Please enter palyer name: " << RESET;
	string name;
	cin >> name;
	Player player(name);
    game.start(player);
    cout << "game ended" << endl;
    return 0;
}
