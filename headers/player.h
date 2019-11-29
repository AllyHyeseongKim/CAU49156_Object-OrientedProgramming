#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"

typedef enum {HRM, Politic, MSoldier, War, FindUnit, GetUnit, MoveUnit} Command;

class Player : public User {
public:

    // 현 영지에서
    // 1: 인사, 2: 내정, 3: 병사, 4: 전쟁
    void command(int command_num, GameUnit selected_unit);
    void command(int command_num, GameUnit selected_unit, int need_num);
    void command_hire(GameUnit hiring_unit, GameUnit hired_unit);
    void command_war(GameUnit selected_unit, int soldier, State attack_state);

};

#endif