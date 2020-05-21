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
            for(int j = 0; j < list.size(); j++) {
                if(list[j].get_status() == undeveloped || list[j].get_status() == developed) {
                    if(list[j].get_can_move()){
                        own_states[i]->set_unit_status(list[j], developed);
                        break;
                    }
                }
            }


            for(int j = 0; j < list.size(); j++) {
                std::vector<GameUnit> &list = own_states[i]->get_unit_list();
                if((list[j].get_status() == hired || list[j].get_status() == munonarch)
                && total_rice > 1000) {
                    if(list[j].get_can_move()){
                        own_states[i]->recurit_soldier(list[j], 2000);
                    }
                }
            }

            own_states[i]->set_soldier_degree( own_states[i]->get_soldier_degree() + 30);
        }
    }
}


std::pair<GameUnit*, int> GameAI::attack_state(State &ai_state, State &enamy_state, GameUnit &enamy_unit) {
    GameUnit *unit;

    std::vector<GameUnit> &list = ai_state.get_unit_list();
    for(int i = 0; i < list.size(); i++) {
        if(list[i].get_status() == hired || list[i].get_status() == munonarch) {
            unit = &list[i]; // unit = &unit[j]; 수정
                break;
        }
    }
    ai_state.war(*unit, ai_state.get_state_soilder(), enamy_state, enamy_unit);
    return make_pair(unit, ai_state.get_state_soilder());
}


GameUnit* GameAI::defence_state(State& attecked_state, State &enamy_state, GameUnit &enamy_unit, int num_enamy_soldier) {
    std::vector<GameUnit>& unit_list= attecked_state.get_unit_list();
    
    for(int i = 0; i < unit_list.size(); i++) {
        if(unit_list[i].get_status() == munonarch || unit_list[i].get_status() == hired) {
            attecked_state.defense(unit_list[i], enamy_state, enamy_unit, num_enamy_soldier);
            return &unit_list[i];
        }
    }
    return &unit_list[0];
}
