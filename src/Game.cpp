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
	//use select to check if stdin is readable
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

void Game::start(Player &player)
{
	cout << YELLOW << BOLD << "Welcome " << player.get_name() << "!" << endl;
	cout << YELLOW << BOLD << "You have " << GAME_DURATION_SECONDS << " seconds to guess the missing charachter!" << RESET << endl;
	cout << "press ENTER to start..." << endl;
	cin.ignore();
	cin.get();
	
	cout << endl;

	this->init();
	this->filter_uuids();
	this->print_uuids();
	this->start_timer();

	string input;
	cout << "char " << this->_randomChar << endl;
	int time_left = 0;
	while((time_left = this->get_time_left()))
	{
		std::cout << YELLOW << BOLD << "\rTime left: " << time_left 
				<< " " << BLUE << BOLD << "Please enter the missing char: " << std::flush;
	
		if (check_input(input))
			break ;
		usleep(1000000);
	}
	this->result(input, player, time_left);
}

void Game::result(string &input, Player &player, int time_left)
{
	bool result = false;
	cout << endl;
	if (time_left <= 0)
	{
		cout << RED << BOLD << "Time is up!" << RESET << endl;
	}
	if (time_left > 0 && input.length() == 1 && input[0] == _randomChar)
	{
		result = true;
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
