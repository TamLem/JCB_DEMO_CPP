#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include "Player.hpp"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Game
{
	private:
		vector<string> _uuids;
		vector<string> _filteredUuids;
		char _randomChar;
		
	public:
		Game(/* args */);
		~Game();
		void init(void);
		void start(Player &player);
		void filter_uuids(void);

		/* utils */
		char generate_random_char();
		string generate_random_uuid();
		void print_uuids();
};







#endif