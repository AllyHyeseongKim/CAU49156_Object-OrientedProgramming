#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"

typedef enum {HR = 1, Politic, Soldier, War, GetSoldier, TrainSolider, Defend, FindUnit, GetUnit, MoveUnit} Command;
class Player : public User {
public:
    Player(std::string user_id);
    // 현 영지에서
    void command(Command command_num, GameUnit &selected_unit);
    void command(Command command_num, GameUnit &selected_unit, GameUnit &unhired_unit);
    void command(Command command_num, GameUnit &selected_unit, int num);
    void command(Command command_num, GameUnit &selected_unit, StateId state_id);
    void command(Command command_num, GameUnit &selected_unit, State &enamy_state, GameUnit &enamy_unit, int enamy_soldier);
};

#endif