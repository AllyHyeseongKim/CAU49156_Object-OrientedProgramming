#ifndef GAME_AI_H
#define GAME_AI_H

#include "user.h"

class GameAI : public User {
public:
    GameAI(std::string user_id);
    void AI_algo(int total_turn);
    void defence_state(State& attecked_state, State &enamy_state, GameUnit &enamy_unit, int num_enamy_soldier);
    StateId attack_state(State &enamy_state, GameUnit &enamy_unit);
    
private:
};

#endif