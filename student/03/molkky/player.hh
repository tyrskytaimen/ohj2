#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

class Player
{
public:
    Player(std::string name);
    std::string get_name() const;
    int get_points() const;
    bool has_won() const;
    void add_points(int points);

private:
    std::string name_;
    int points_ = 0;
};

#endif // PLAYER_HH
