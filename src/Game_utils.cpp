#include "Game.hpp"

string Game::generate_random_uuid()
{
    string uuid_str = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    return uuid_str;
}

char Game::generate_random_char()
{
    char c = rand() % 16;
    if (c < 10)
        c += '0';
    else
        c += 'a' - 10;
    return c;
}

void Game::filter_uuids(void)
{
	if (_uuids.size() == 0)
		return ;
	cout << YELLOW << BOLD << "Filtering uuids: " << RESET << endl;
	for (vector<string>::iterator it = this->_uuids.begin(); it != this->_uuids.end(); it++)
	{
		if ((*it).find(_randomChar) != string::npos)
		{
			this->_filteredUuids.push_back(*it);
		}
	}
}

void Game::print_uuids()
{
	for (vector<string>::iterator it = this->_filteredUuids.begin(); it != this->_filteredUuids.end(); it++)
	{
		cout << GREEN << BOLD <<  *it << RESET << endl;
	}
}

bool Game::get_game_over()
{
	return this->_gameOver;
}