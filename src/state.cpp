#include "../headers/state.h"
#include "../headers/user.h"

State::State(User &owner, StateId state_id) {
    state_owner = &owner;
    this->state_id = state_id;
    agriculture_degree = 100;
    soldier_degree = 20;
    state_soldier = 0;
}

void State::agriculture(GameUnit &selected_unit) {
    assert(selected_unit.get_can_move());
    selected_unit.set_can_move(false);
    agriculture_degree += selected_unit.get_political * 0.5;
}

void State::recurit_soldier(GameUnit &selected_unit, int num_soldier) {
    assert(selected_unit.get_can_move());
    assert(state_owner->get_total_rice >= 0.5 * num_soldier);
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

    hired_unit.set_can_move(false);
    hirng_unit.set_status(hired);
}

void State::move_unit(GameUnit &selected_unit, StateId moved_state_id) {
    unit_list.erase(find(unit_list.begin(), unit_list.end(), selected_unit));

    State &state = state_owner->find_own_state(moved_state_id);
    state.unit_list.push_back(selected_unit);
}

void State::war(GameUnit &selected_unit, int soldier, State &enamy_state, GameUnit &enamy_unit) {
    assert(selected_unit.get_can_move());
    assert(state_soldier >= soldier);
    srand((unsigned int)time(0));

    int enamy_unit_index;

    if (check_win(selected_unit, soldier, enamy_state, enamy_unit, enamy_state.state_soldier)) {
        state_soldier = state_soldier - soldier * 0.1;
        enamy_state.state_owner = state_owner;
    }
    else {
        state_soldier = state_soldier - soldier * 0.5;
    }
}

void State::defense(GameUnit &selected_unit, State &enamy_state, GameUnit &enamy_unit, int enamy_soldier) {
    if (check_win(selected_unit, state_soldier, enamy_state, enamy_unit, enamy_soldier)) {
        state_soldier = state_soldier * 0.9;
    }
    else {
        state_soldier = 0;
        for (GameUnit &unit: unit_list)
            if (unit.get_status() == hired)
                unit.set_status(developed);
    }
}

bool State::check_win(GameUnit &selected_unit, int num_friendly_soldier, State &enamy_state, GameUnit &enamy_unit, int num_enamy_soldier) {
        int friendly_power = soldier_degree * num_friendly_soldier 
            + (selected_unit.get_strength() + selected_unit.get_leadearship() + selected_unit.get_wisdom()) / 3;

        int enamy_power = enamy_state.soldier_degree * num_enamy_soldier 
            + (enamy_unit.get_strength() + enamy_unit.get_leadearship() + enamy_unit.get_wisdom()) / 3;

        return friendly_power >= enamy_power;
    }