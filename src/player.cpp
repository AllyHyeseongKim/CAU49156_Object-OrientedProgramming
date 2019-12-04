#include "../headers/player.h"

Player::Player(std::string user_id) : User(user_id) {
    this->user_id = user_id;
    this->total_rice = 5000;
}

void Player::command(Command command_num, GameUnit &selected_unit) {
    std::vector<State*>::iterator state;
    for(state = own_states.begin(); state != own_states.end(); state++)
        if((*state)->is_hired(selected_unit))
            break;

    switch (command_num) {
    case FindUnit:
        (*state)->search_unit(selected_unit);
        break;
    case Politic:
        (*state)->agriculture(selected_unit);
        break;;
    case TrainSolider:
        (*state)->train_soldier(selected_unit);
        break;
    }
}

void Player::command(Command command_num, GameUnit &selected_unit, GameUnit &unhired_unit) {
    std::vector<State*>::iterator state;
    for(state = own_states.begin(); state != own_states.end(); state++)
        if((*state)->is_hired(selected_unit))
            break;

    switch (command_num)
    {
    case GetUnit:
        (*state)->hire_unit(unhired_unit, selected_unit);
        break;
    }
}

void Player::command(Command command_num, GameUnit &selected_unit, int num) {
    std::vector<State*>::iterator state;
    for(state = own_states.begin(); state != own_states.end(); state++)
        if((*state)->is_hired(selected_unit))
            break;

    switch (command_num) {
    case GetSoldier:
        (*state)->recurit_soldier(selected_unit, num);
        break;
    }
}


void Player::command(Command command_num, GameUnit &selected_unit, StateId state_id) {
    std::vector<State*>::iterator state;
    for(state = own_states.begin(); state != own_states.end(); state++)
        if((*state)->is_hired(selected_unit))
            break;

    switch (command_num) {
    case MoveUnit:
        (*state)->move_unit(selected_unit, state_id);
        break;
    }
}

void Player::command(Command command_num, GameUnit &selected_unit, State &enamy_state, GameUnit &enamy_unit, int enamy_soldier) {
    std::vector<State*>::iterator state;
    for(state = own_states.begin(); state != own_states.end(); state++)
        if((*state)->is_hired(selected_unit))
            break;

    switch (command_num) {
        case Defend:
        (*state)->defense(selected_unit, enamy_state, enamy_unit, enamy_soldier);
        break;
    }
    
}


// typedef enum {Politic, GetSoldier, TrainSolider, War, Defend, FindUnit, GetUnit, MoveUnit} Command;