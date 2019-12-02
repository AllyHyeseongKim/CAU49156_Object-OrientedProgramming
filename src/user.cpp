// #include "../headers/state.h"
#include "../headers/user.h"

User::User(std::string user_id, StateId state_id) {
    this->user_id = user_id;
    this->own_states.push_back(new State(state_id, ""));
    total_rice = 500;
}


State& User::find_own_state(StateId state_id) {
    for(int i = 0; i < own_states.size(); i++) {
        if(own_states[i]->get_state_id() == state_id)
            return *own_states[i];
    }
    assert(false);
}

int User::get_total_rice() {
    return total_rice;
}

void User::set_total_rice(int rice) {
    total_rice = rice;
}

bool User::chk_own_state(int state_id) {
    for(int i = 0; i < own_states.size(); i++) {
        if(own_states[i]->get_state_id() == state_id)
            return true;
    }
    return false;
}