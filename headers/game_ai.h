#ifndef GAME_AI_H
#define GAME_AI_H

#include "user.h"

class GameAI : public User {
public:
    GameAI(std::string user_id);
    void AI_algo(int total_turn);
    void defence_state();
    void attack_state();
    
private:
};

#endif