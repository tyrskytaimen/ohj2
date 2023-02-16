#include "player.hh"
#include <iostream>

Player::Player(std::string name):
    name_(name)
{

}

std::string Player::get_name() const
{
    return name_;
}

int Player::get_points() const
{
    return points_;
}

bool Player::has_won() const
{
    return points_ == 50;
}

void Player::add_points(int points)
{
    if (points_ + points > 50)
    {
        points_ = 25;
        std::cout << name_ << " gets penalty points!" << std::endl;
    }
    else
    {
        points_ += points;
    }
}
