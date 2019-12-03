#include "../headers/player.h"

Player::Player(std::string user_id) : User(user_id) {
    this->user_id = user_id;
    this->total_rice = 5000;
}