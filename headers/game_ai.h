#ifndef GAME_AI_H
#define GAME_AI_H

#include "user.h"

class GameAI : public User {

public:
    void AI_algo();
    void defence_state();
    void attack_state();
    
private:
};

#endif