#include "../headers/game_controller.h"

GameController::GameController() {
    this->total_turn = 1;
}

User* GameController::get_user_turn() {
    return user_turn;
}

int GameController::get_total_turn() {
    return total_turn;
}

// total_turn에 따른 현재 YYYY/MM 반환 알고리즘 작성
string GameController::get_date() {
    int yyyy = 1392, mm = 1;
    if(total_turn % 12 != 0) {
        yyyy += total_turn / 12;
        mm = total_turn % 12;
    }
    else {
        yyyy += (total_turn-1) / 12;
        mm = 12;
    }
    return to_string(yyyy) + "년/" + to_string(mm) + "월";
}

vector<User*> GameController::get_users() {
    return users;
}

vector<State*> GameController::get_states() {
    return states;
}

void GameController::set_user_turn(User* user) {
    this->user_turn = user;
}

void GameController::set_states(string game_state_file) {
    ifstream data(game_state_file);

    if(!data.is_open()) {
        cout << "게임 영지 데이터 파일이 없습니다.\n";
        exit(1);
    }

    State* state;
    while(!data.eof()) {
        string line;
        vector<string> token;
        vector<string>::iterator iter;

        getline(data, line);

        stringstream token_line(line);
        string tok;

        while(getline(token_line, tok, '/')) {
            if(tok.front() == ':') {
                tok.erase(0,1);
            }
            token.push_back(tok);
        } 

        if(line.front() == ':') { // 만약 해당 line이 State에 관한 정보라면

            // state 객체 생성
            state = new State(static_cast<StateId>(atoi(token[0].c_str())), token[1]);
            this->states.push_back(state);
        
            // near_state 설정
            for(iter = token.begin() + 2; iter != token.end(); iter++) {
                state->set_near_state(static_cast<StateId>(atoi((*iter).c_str())));
            }

        } else {  // 만약 해당 line이 GameUnit에 관한 정보라면
            
            // 영웅 스탯 int 형으로 변환
            int status[5];
            for(int i=0; i<5; i++) {
                status[i] = atoi(token[i+1].c_str());
            }

            state->add_unit_list(GameUnit(token[0], 
                                status[0], status[1], status[2], status[3], status[4],
                                static_cast<UnitStatus>(atoi(token[6].c_str()))));   
        }
    }
    data.close();
}

void GameController::add_user(User* user) {
    users.push_back(user);
}

User* GameController::next_user_turn(User* user) {
    vector<User*>::iterator iter;
    for(iter = users.begin(); iter != users.end(); iter++) {
        if(*iter == user) {
            break;
        }
    }
    if(iter + 1 != users.end()) {
        return *(iter + 1);
    }
    return *(users.begin());
}

void GameController::increase_total_turn() {
    total_turn += 1;
}

State *GameController::get_state_by_id(StateId id) {
    for(int i = 0; i < states.size(); i++) {
        if(states[i]->get_state_id() == id)
            return states[i];
    }
    return NULL;
}

Judge GameController::check_game_judge() {
    // 만약 9개의 영지를 모두 점령했다면 승리
    if((users.at(0)->get_own_states()).size() == 9) {
        return WIN;
    } else if((users.at(0)->get_own_states()).size() == 0) {
        return LOSE;
    } else {
        return NOTHING;
    }
}