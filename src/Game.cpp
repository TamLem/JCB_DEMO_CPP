#include "Game.hpp"

Game::Game(): _gameOver(false)
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

void Game::start_timer()
{
	this->_startTime = second_clock::local_time();
	this->_endTime = this->_startTime + seconds(GAME_DURATION_SECONDS);
	this->_duration = this->_endTime - this->_startTime;
}

int Game::get_time_left()
{
	ptime now = second_clock::local_time();
	time_duration time_left = this->_endTime - now;
	return time_left.total_seconds();
}

bool Game::check_input(string &input)
{
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	select(1, &fds, NULL, NULL, &tv);
	if (FD_ISSET(0, &fds))
	{
		cin >> input;
		return true;
	}
	return false;
}

void Game::welcome_player(Player &player)
{
	if (player.get_score() == 0)
		cout << YELLOW << BOLD << "Welcome " << player.get_name() << "!" << endl;
	else
		cout << YELLOW << BOLD << "Welcome back " << player.get_name() << "!" << endl;
	cout << YELLOW << BOLD << "You have " << GAME_DURATION_SECONDS << " seconds to guess the missing charachter! [0-9a-f]" << RESET << endl;
	cout << GREEN << "press ENTER to start... or type 'exit' to quit" << endl;
	cin.ignore();
	string input;
	std::getline(cin, input);
	if (input == "exit")
		exit(0);
	cout << endl;
}

void Game::start(Player &player)
{
	this->welcome_player(player);
	this->init();
	this->filter_uuids();
	this->print_uuids();
	this->start_timer();

	string input;
	int time_left = 0;
	bool result = false;
	cout << "missing char " << this->_randomChar << endl;
	while((time_left = this->get_time_left()))
	{
		if (check_input(input))
		{
			if ((result = this->check_result(input)))
			{
				break;
			}
		}
		else
		{
			std::cout << YELLOW << BOLD << "\rTime left: " << time_left 
					<< " " << BLUE << BOLD << "Please enter the missing char: " << std::flush;
		}
		usleep(100000);
	}
	this->show_score(player, time_left, result);
}

bool Game::check_result(string &input)
{
	if (input.length() > 1 || string("0123456789abcdef").find(input) == string::npos)
	{
		cout << RED << BOLD << "Invalid input! Guess from [0-9a-f]" << RESET << endl;
		return false;
	}
	if (input[0] == this->_randomChar)
		return true;
	cout << RED << BOLD << "Wrong!" << RESET << endl;
	return false;
}


void Game::show_score(Player &player, int time_left, bool result)
{
	if (time_left <= 0)
	{
		cout << RED << BOLD << "Time is up!" << RESET << endl;
	}
	if (result)
	{
		cout << GREEN << BOLD << "You win!" << RESET << endl;
		player.add_score(time_left);
	}
	else
	{
		cout << RED << BOLD << "You lose!" << endl << 
			"The missing char was " << this->_randomChar << RESET << endl;
	}
	cout << GREEN << BOLD << "Score: " << RESET << (result ? time_left : 0) << endl;
	cout << GREEN << BOLD << "Total score: " << RESET << player.get_score() << endl;
	this->_gameOver = !result;
}
