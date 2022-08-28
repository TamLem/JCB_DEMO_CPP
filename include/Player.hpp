#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Player
{
	private:
		int _score;
		string _name;
	public:
		Player(/* args */);
		Player(string &name);
		~Player();

		void add_score(int score);
};






#endif