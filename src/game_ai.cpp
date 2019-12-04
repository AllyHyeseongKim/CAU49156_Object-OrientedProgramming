#include "../headers/game_ai.h"
#include "../headers/game_controller.h"

GameAI::GameAI(std::string user_id): User(user_id) {
    this->user_id = user_id;
    this->total_rice = 5000;
}

void GameAI::AI_algo(int total_turn) {
    if(total_turn % 10 == 0) {
        for(int i = 0; i < own_states.size(); i++) {
            own_states[i]->set_agriculture_degree(own_states[i]->get_agriculture_degree() + 25);
        }
    }
    if(total_turn % 15 == 0) {
        for(int i = 0; i < own_states.size(); i++) {
            std::vector<GameUnit> &list = own_states[i]->get_unit_list();
            for(int j = 0; j < list.size(); i++) {
                if(list[j].get_status() == undeveloped || list[j].get_status() == developed) {
                    own_states[i]->set_unit_status(list[j], developed);
                    break;
                }
            }


            for(int j = 0; j < list.size(); i++) {
                std::vector<GameUnit> &list = own_states[i]->get_unit_list();
                if((list[j].get_status() == hired || list[j].get_status() == munonarch)
                && total_rice > 1000) {
                    own_states[i]->recurit_soldier(list[j], 2000);
                }
            }

            own_states[i]->set_soldier_degree( own_states[i]->get_soldier_degree() + 30);
        }
    }
}


StateId GameAI::attack_state(State &enamy_state, GameUnit &enamy_unit) {
    GameUnit *unit;
    for(int i = 0; i < own_states.size(); i++) {
        std::vector<GameUnit> &list = own_states[i]->get_unit_list();
        std::vector<StateId> &near_state = own_states[i]->get_near_state();

        for(int j = 0; j < list.size(); i++) {
            if(list[j].get_status() == hired || list[j].get_status() == munonarch) {
                unit = &unit[j];
                break;
            }
        }
        for(StateId &id: near_state) {
            if(!chk_own_state(id)) {
                own_states[i]->war(*unit, own_states[i]->get_state_soilder(), enamy_state, enamy_unit);
                return id;
            }
        }
    }
}


void GameAI::defence_state(State& attecked_state, State &enamy_state, GameUnit &enamy_unit, int num_enamy_soldier) {
    std::vector<GameUnit>& unit_list= attecked_state.get_unit_list();
    
    for(int i = 0; i < unit_list.size(); i++) {
        if(unit_list[i].get_status() == munonarch || unit_list[i].get_status() == hired)
            attecked_state.defense(unit_list[i], enamy_state, enamy_unit, num_enamy_soldier) ;
    }
}