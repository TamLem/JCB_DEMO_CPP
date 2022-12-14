#include "Player.hpp"

Player::Player(): _score(0), _name("player1")
{
}

Player::Player(string &name): _name(name), _score(0)
{
}

Player::~Player()
{
}

void Player::add_score(int score)
{
	this->_score += score;
}

int Player::get_score()
{
	return this->_score;
}

string& Player::get_name()
{
	return this->_name;
}