#include "../headers/game_controller.h"

GameController::GameController(): total_turn(0) {
    // ...
}

void GameController::set_state(string game_state_file) {
    ifstream data(game_state_file);

    if(!data.is_open()) {
        cout << "게임 영지 데이터 파일이 없습니다.\n";
        exit(1);
    }

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
            State* state = new State(static_cast<StateId>(atoi(token[0].c_str())), token[1]);
            this->states.push_back(state);
        
            // near_state 설정
            for(iter = token.begin() + 2; iter != token.end(); iter++) {
                state->set_near_state(static_cast<StateId>(atoi((*iter).c_str())));
            }

        } else {  // 만야 해당 line이 GameUnit에 관한 정보라면
            
            // 영웅 스탯 int 형으로 변환
            int status[5];
            for(int i=0; i<5; i++) {
                status[i] = atoi(token[i+1].c_str());
            }

            GameUnit *game_unit = new GameUnit(token[0], 
                                status[0], status[1], status[2], status[3], status[4], 
                                static_cast<UnitStatus>(atoi(token[6].c_str())));
        }
    }
    data.close();
}

