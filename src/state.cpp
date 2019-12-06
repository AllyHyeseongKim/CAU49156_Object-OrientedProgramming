#include "../headers/user.h"
#include "../headers/state.h"

State::State() {}

State::State(StateId state_id, string state_name) {
    this->state_id = state_id;
    this->state_name = state_name;
    agriculture_degree = 100;
    soldier_degree = 20;
    state_soldier = 0;
}

StateId State::get_state_id() {
    return state_id;
}

std::string State::get_state_name() {
    return state_name;
}

int State::get_agriculture_degree() {
    return agriculture_degree;
}

void State::set_agriculture_degree(int degree) {
    agriculture_degree = degree;
}

void State::set_state_owner(User *owner) {
    this->state_owner = owner;
}

void State::set_near_state(StateId state_id) {
    near_states.push_back(state_id);
}

std::vector<StateId>& State::get_near_state() {
    return near_states;
}

void State::add_unit_list(GameUnit unit) {
    unit_list.push_back(unit);
}

void State::agriculture(GameUnit &selected_unit) {
    assert(selected_unit.get_can_move());
    selected_unit.set_can_move(false);
    agriculture_degree += selected_unit.get_political() * 0.5;
}

void State::recurit_soldier(GameUnit &selected_unit, int num_soldier) {
    assert(selected_unit.get_can_move());
    assert(state_owner->get_total_rice() >= 0.5 * num_soldier);
    assert(soldier_capacity >= state_soldier);

    selected_unit.set_can_move(false);
    state_soldier += num_soldier;
    state_owner->set_total_rice(state_owner->get_total_rice() - int(0.5 * num_soldier + 0.5));
}

void State::train_soldier(GameUnit &selected_unit) {
    assert(selected_unit.get_can_move());

    selected_unit.set_can_move(false);
    soldier_capacity += selected_unit.get_leadearship() * 0.3;
}

void State::set_soldier_degree(int degree) {
    soldier_degree = degree;
}

int State::get_soldier_degree() {
    return soldier_degree;
}

void State::search_unit(GameUnit &selected_unit) {
    assert(selected_unit.get_can_move());
    srand((unsigned int)time(0));

    for(GameUnit &unit: unit_list) {
        if(unit.get_status() == undeveloped) {
            unit.set_status(developed);
            selected_unit.set_can_move(false);
            break;
        }
    }
}

void State::hire_unit(GameUnit &hirng_unit, GameUnit &hired_unit) {
    assert(hired_unit.get_can_move());
    srand((unsigned int)(time(0)));
    double attraction = hired_unit.get_attraction();
    attraction = (attraction > 50) ? attraction * 1.005 : attraction * 0.999;

    hired_unit.set_can_move(false);

    if ((rand() % 100) < 50 + attraction)
        return;
    hirng_unit.set_status(hired);

    // unit_list에 추가하기
}

void State::move_unit(GameUnit &selected_unit, StateId moved_state_id) {
    GameUnit unit = selected_unit;

    for(int i = 0; i < unit_list.size(); i++) {
        if (unit_list[i] == selected_unit) {
            unit_list.erase(unit_list.begin() + i);
            break;
        }
    }
    // unit_list.erase(find(unit_list.begin(), unit_list.end(), selected_unit));

    State &state = state_owner->find_own_state(moved_state_id);
    state.unit_list.push_back(unit);
}

bool State::war(GameUnit &selected_unit, int soldier, State &enamy_state, GameUnit &enamy_unit) {
    assert(selected_unit.get_can_move());
    assert(state_soldier >= soldier);
    srand((unsigned int)time(0));

    int enamy_unit_index;

    if (check_win(selected_unit, soldier, enamy_state, enamy_unit, enamy_state.state_soldier)) {
        state_soldier = state_soldier - soldier * 0.1;
        enamy_state.state_owner = state_owner;
        state_owner->add_state(&enamy_state);
        return true;
    }
    else {
        state_soldier = state_soldier - soldier * 0.5;
        return false;
    }
}

bool State::defense(GameUnit &selected_unit, State &enamy_state, GameUnit &enamy_unit, int enamy_soldier) {
    if (check_win(selected_unit, state_soldier, enamy_state, enamy_unit, enamy_soldier)) {
        state_soldier = state_soldier * 0.9;
        return true;
    }
    else {
        state_soldier = 0;
        for (GameUnit &unit: unit_list)
            if (unit.get_status() == hired)
                unit.set_status(developed);
        state_owner->erase_state(this);
        return false;
    }
}

bool State::check_win(GameUnit &selected_unit, int num_friendly_soldier, State &enamy_state, GameUnit &enamy_unit, int num_enamy_soldier) {
    int friendly_power = soldier_degree * num_friendly_soldier
            + (selected_unit.get_strength() + selected_unit.get_leadearship() + selected_unit.get_wisdom()) / 3;

    int enamy_power = enamy_state.soldier_degree * num_enamy_soldier
            + (enamy_unit.get_strength() + enamy_unit.get_leadearship() + enamy_unit.get_wisdom()) / 3;

    return friendly_power >= enamy_power;
}


bool State::is_hired(GameUnit &selected_unit) {
    for(int i = 0; i < unit_list.size(); i++)
        if(unit_list[i] == selected_unit)
            return true;

    return false;
} 

   
std::vector<GameUnit>& State::get_unit_list() {
    return unit_list;
}

void State::set_unit_status(GameUnit &unit, UnitStatus status) {
    for(int i = 0; i < unit_list.size(); i++) {
        if(unit == unit_list[i]) {
            unit_list[i].set_status(status);
            return;
        }
    }

    assert(true);
}

int State::get_state_soilder() {
    return state_soldier;
}

void State::reset_can_move() {
    for(int i = 0; i < unit_list.size(); i++) {
        unit_list[i].set_can_move(true);
    }
}