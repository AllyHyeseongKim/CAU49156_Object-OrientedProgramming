#include "../headers/state.h"
#include "../headers/user.h"

State::State(User *owner, StateId state_id) {
    state_owner = owner;
    this->state_id = state_id;
    agriculture_degree = 100;
    soldier_degree = 20;
    state_soldier = 0;
    switch (state_id)
    {
    case Hamgyeongdo:
        unit_list.push_back(GameUnit("Lee Seonggye", 95, 85, 60, 75, 80, munonarch));
        unit_list.push_back(GameUnit("Yoongwan", 75, 94, 62, 50, 55, undeveloped));
        unit_list.push_back(GameUnit("Yeongaesomun", 70 ,82 ,62 ,75 ,72 , undeveloped));
        unit_list.push_back(GameUnit("Eulpaso", 23, 43, 89, 92, 80,  undeveloped));
        unit_list.push_back(GameUnit("DaeJoyeong", 83, 90, 32, 64, 80,  developed));
        break;
    case Pyongando:
        unit_list.push_back(GameUnit("Hong Gyeongrae", 70, 72, 65, 80, 80, developed));
        unit_list.push_back(GameUnit("Myocheong", 45, 55, 70, 90, 90,  undeveloped));
        unit_list.push_back(GameUnit("Jangjisang", 40, 60, 85, 85, 65,  undeveloped));
        break;
    case Hwanghaedo:
        unit_list.push_back(GameUnit("Gwangjong", 85, 85, 80, 90, 90, munonarch));
        unit_list.push_back(GameUnit("Lim kkeokjeong", 90, 65, 20, 20, 50, developed));
        unit_list.push_back(GameUnit("Kim Gu", 65, 80, 85, 85, 80, undeveloped));
        unit_list.push_back(GameUnit("Ahn Junggeun", 70, 85, 75, 60, 60, undeveloped));
        unit_list.push_back(GameUnit("Cheokjungyeong", 100, 45, 20, 20, 30, undeveloped));
        break;
    case Gangwondo:
        unit_list.push_back(GameUnit("Ii", 15, 20, 80, 85, 80, undeveloped));
        unit_list.push_back(GameUnit("Sinsaimdang", 10, 20, 85, 70, 65, undeveloped));
        unit_list.push_back(GameUnit("Gungye", 80, 65, 55, 50, 60, undeveloped));
        unit_list.push_back(GameUnit("Wanggeon", 75, 70, 60, 85, 80, developed));
        unit_list.push_back(GameUnit("Kim Siseup", 10, 20, 80, 80, 60, undeveloped));
        break;
    case Gyeonggido:
        unit_list.push_back(GameUnit("Jeong Dojeon", 15, 30, 95, 90, 85, undeveloped));
        unit_list.push_back(GameUnit("Hwang Hui", 10, 25, 90, 95, 90, undeveloped));
        unit_list.push_back(GameUnit("Gwonryul", 85, 85, 70, 65, 70, developed));
        unit_list.push_back(GameUnit("Seohui", 30, 30, 80, 80, 60, undeveloped));
        unit_list.push_back(GameUnit("Jeong Yakyong", 20, 45, 80, 90, 65, undeveloped));
        break;
    case Chungcheongdo:
        unit_list.push_back(GameUnit("Lee Sunsin", 85, 100, 75, 65, 90, undeveloped));
        unit_list.push_back(GameUnit("Choe Yeong", 90, 90, 60, 55, 45, undeveloped));
        unit_list.push_back(GameUnit("Choe Ikhyeon", 45, 60, 70, 75, 70,  developed));
        unit_list.push_back(GameUnit("Kim Jwajin", 80, 85, 70, 50, 60, undeveloped));
        break;
    case Gyeongsangdo:
        unit_list.push_back(GameUnit("Moonmuwang", 55, 75, 80, 85, 90, munonarch));
        unit_list.push_back(GameUnit("Jeong Mongju", 20, 30, 85, 85, 70, undeveloped));
        unit_list.push_back(GameUnit("Lee Hwang", 10, 20, 95, 75, 60, undeveloped));
        unit_list.push_back(GameUnit("Yoo Seongryong", 20, 40, 75, 90, 85, undeveloped));
        unit_list.push_back(GameUnit("Kim Yusin", 80, 90, 70, 80, 75, developed));
        break;
    case Jeollado:
        unit_list.push_back(GameUnit("Gyeonhwon", 5, 80, 75, 80, 90, munonarch));
        unit_list.push_back(GameUnit("Jangbogo", 85, 85, 50, 35, 50, undeveloped));
        unit_list.push_back(GameUnit("Jeong Bongjun", 80, 90, 70, 70, 75, undeveloped));
        unit_list.push_back(GameUnit("Gyebaek", 90, 85, 60, 45, 60, developed));
        unit_list.push_back(GameUnit("Wangin", 10, 10, 80, 80, 80, undeveloped));
        break;
    case Jejudo:
        unit_list.push_back(GameUnit("Kim Mandeok", 20, 30, 80, 85, 90, undeveloped));
        unit_list.push_back(GameUnit("Kim Jeonghui", 20, 20, 75, 85, 75, developed));
        break;
    }

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

StateId State::get_state_id() {
    return state_id;
}