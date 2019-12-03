#include "../headers/state.h"
#include "../headers/user.h"

User::User(std::string user_id) {
    this->user_id = user_id;
    total_rice = 5000;
}

State& User::find_own_state(StateId state_id) {
    for(int i = 0; i < own_states.size(); i++) {
        if(own_states[i]->get_state_id() == state_id)
            return *own_states[i];
    }
    assert(false);
}

bool User::chk_own_state(StateId state_id) {
    for(int i = 0; i < own_states.size(); i++) {
        if(own_states[i]->get_state_id() == state_id)
            return true;
    }
    return false;
}

void User::add_state(State* state) {
    this->own_states.push_back(state);
}

std::string User::get_user_id() {
    return user_id;
}

vector<State*> User::get_own_states() {
    return own_states;
}

int User::get_total_rice() {
    return total_rice;
}

void User::set_total_rice(int rice) {
    total_rice = rice;
}

void User::increase_total_rice(int rice) {
    total_rice += rice;
}