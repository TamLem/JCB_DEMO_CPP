#include "Game.hpp"

Game::Game(/* args */)
{
}

Game::~Game()
{
}

void Game::init(void)
{
	std::stringstream counter;

	srand(time(NULL));
	this->_uuids.clear();
	counter << YELLOW << BOLD << "Generating random uuid... " << RESET;
	cout << YELLOW << BOLD << "Initializing game..." << RESET << endl;
	cout << counter.str() << " 0";
	for (int i = 0; i < 100; i++)
	{
		cout << "\r" << counter.str() << i + 1 << ((i + 1) > 9 ? "" : " ");
		usleep(10000);
		cout.flush();
		_uuids.push_back(generate_random_uuid());
	}
	cout << endl;
	cout << YELLOW << BOLD << "Generating random charachter... " << RESET << "1 " << endl;
	_randomChar = generate_random_char();
}

void Game::start(Player &player)
{
	this->init();
	this->filter_uuids();
	this->print_uuids();

	cout << YELLOW << BOLD << "Please enter the missing char: " << _randomChar << RESET;
	char input;
	cin >> input;
	if (input == _randomChar)
	{
		cout << GREEN << BOLD << "You win!" << RESET << endl;
		player.add_score(1);
	}
	else
	{
		cout << RED << BOLD << "You lose!" << RESET << endl;
	}

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

void Game::print_uuids()
{
	for (vector<string>::iterator it = this->_filteredUuids.begin(); it != this->_filteredUuids.end(); it++)
	{
		cout << GREEN << BOLD <<  *it << RESET << endl;
	}
}
