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
        // char_seprator<char> sep("-","/");

        getline(data, line);
        
        if(line.front() == ':') {

            stringstream token_line(line);
            string tok;

            while(getline(token_line, tok, '/')) {
                if(tok.front() == ':') {
                    tok.erase(0,1);
                }
                token.push_back(tok);
            }

            // TOKC tok(line, sep);
            // for(TOKC::iterator i = tok.begin(); i != tok.end(); i++) {
            //     cout << *i << " ";
            // }
        }

        for(iter = token.begin(); iter != token.end(); iter++) {
            cout << *iter << " ";
        }
        cout << "\n";
        
    }
    data.close();
}

