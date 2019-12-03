#include "headers/game_controller.h"

int main(int argc, char *argv[]) {

    GameController game;
    game.set_states("data/game_state_data.txt");    // 나중에 set_user와 합쳐서 set_game으로 발전?
    
    string user_id;
    string hero;

    // 게임 시나리오
    // 나중에 display.cpp 로 빼든가 알아서~
    
    cout << "<한반도 짱을 가려라> 게임에 오신 것을 환영합니다!\n";
    cout << "당신의 ID를 입력해주세요 : ";
    cin >> user_id;
    cout << "당신의 세력을 고르십시오.\n";
    cout << "1. 이성계 (함경도에서 시작)\n";
    cout << "2. 견훤 (전라도에서 시작)\n";
    cout << "3. 문무왕 (경상도에서 시작)\n";
    cout << "4. 고려 광종 (황해도에서 시작)\n";
    cin >> hero;

    State *initial_state;

    switch(atoi(hero.c_str())) {
        case 1:
            cout << "당신은 '이성계'를 선택했습니다! 함경도에서 시작합니다!\n";
            initial_state = game.get_states().at(0); // 함경도
            break;
        case 2:
            cout << "당신은 '견훤'를 선택했습니다! 전라도에서 시작합니다!\n";
            initial_state = game.get_states().at(7); // 전라도
            break;
        case 3:
            cout << "당신은 '문무왕'를 선택했습니다! 경상도에서 시작합니다!\n";
            initial_state = game.get_states().at(6); // 경상도
            break;
        case 4:
            cout << "당신은 '고려 광종'를 선택했습니다! 황해도에서 시작합니다!\n";
            initial_state = game.get_states().at(3); // 황해도
            break;
        default:
            cout << "에러";
    }

    // player 생성, 선택한 영웅에 맞는 영지 추가
    Player *player = new Player(user_id);
    Player *ai = new Player("1234");        // GameAI 만들어지면 수정하기
    player->add_state(initial_state);

    // players에 player 추가
    game.add_player(player);
    game.add_player(ai);

    // 시작 플레이어 - 유저부터 시작한다
    game.set_player_turn(player);

    // 게임 시작
    while(1) { // 게임 종료 조건 넣기

        // 현재 플레이어 설정
        Player* current_player = game.get_player_turn();
        cout << current_player->get_user_id() << "\n";

        // 총 턴과 날짜 표시
        cout << "턴 : " << game.get_total_turn() << " , " << "날짜 : " << game.get_date() << "\n";
        
        // 농업도에 비례해서 식량 수확 (모든 플레이어가)
        if(game.get_date().find("6월")!= std::string::npos || game.get_date().find("9월")!= std::string::npos) {
            cout << "즐거운 수확철~ 식량이 증가합니다!\n";
            
            // 각 유저에 대해
            vector<Player*>::iterator it;
            for(it = game.get_players().begin(); it != game.get_players().end(); it++) {
                // player가 가지고 있는 모든 영지에 대해
                vector<State*> player_states = (*it)->get_own_states();
                vector<State*>::iterator iter;
                int total_gain = 0;

                for(iter = player_states.begin(); iter != player_states.end(); iter++) {
                    total_gain += (*iter)->get_agriculture_degree() * 20;
                }

                (*it)->increase_total_rice(total_gain);
            }
        }

        // 플레이어 명령
        string next;
        cin >> next;

        game.increase_total_turn();;
        game.set_player_turn(game.next_player_turn(current_player));
    }

    Player *me = game.get_players().at(0);
    // GameAI *ai = game.get_players().at(1);    // 이거는 vector<Player*>에 못들어가잖아 헐
    
    cout << (me->get_total_rice()) << "\n";
    cout << (me->get_user_id()) << "\n";
    cout << (me->find_own_state(Hamgyeongdo).get_state_name()) << "\n";
    cout << (me->find_own_state(Pyongando).get_state_name()) << "\n";

    // 마지막에 game에서 동적할당된 state 등을 delete 해주기
    // player 들도 동적할당되서 delete 필요

    return 0;
}