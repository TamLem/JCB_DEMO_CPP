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

void Game::read_input(string &input)
{
	auto io_thread = std::thread([&]() {
		cin >> input;
	});
}

void Game::start(Player &player)
{
	this->init();
	this->filter_uuids();
	this->print_uuids();
	this->start_timer();

	// time_iterator titr(this->_startTime, seconds(1));
	string input;

	auto future = std::async(std::launch::async, [](){
		string str;
		cin >> str;
		return str;
    });

	std::mutex mtx;
	bool input_received = false;
	auto io_thread = std::thread([&]() {
		// cin >> input;
		if (future.wait_for(std::chrono::seconds(5)) == std::future_status::ready)
		{
			mtx.lock();
			input_received = true;
			mtx.unlock();
		}
	});

	cout << "char " << this->_randomChar << endl;
	int time_left = this->get_time_left();
	while(time_left > 0)
	{
		std::cout << YELLOW << BOLD << "\rTime left: " << time_left 
				<< " " << BLUE << BOLD << "Please enter the missing char: " << std::flush;
	
		mtx.lock();
		if (input_received)
		{
			mtx.unlock();
			break ;
		}
		mtx.unlock();
		if (!input.empty())
		{
			break;
		}
		usleep(1000000);
		time_left = this->get_time_left();
	}
	io_thread.join();
	
	cout << endl;
	if (time_left <= 0)
	{
		cout << RED << BOLD << "Time is up!" << RESET << endl;
		cout << RED << BOLD << "You lose!" << RESET << endl;
		exit(0);
	}
	input = future.get();
	cout << input << endl;
	if (input[0] == _randomChar)
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
