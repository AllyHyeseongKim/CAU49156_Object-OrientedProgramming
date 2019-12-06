#include "headers/game_controller.h"

int main(int argc, char *argv[]) {

    GameController game;
    game.set_states("data/game_state_data.txt");    // 나중에 set_user와 합쳐서 set_game으로 발전?
    
    string user_id;
    string hero;

    // 게임 시나리오
    // 나중에 display.cpp 로 빼든가 알아서~
    
    cout << "<Total War : KOREA> 게임에 오신 것을 환영합니다!\n";
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
    cout << "\n";

    // player 생성, 선택한 영웅에 맞는 영지 추가
    Player *player = new Player(user_id);
    GameAI *ai = new GameAI("AI");
    player->add_state(initial_state);
    
    // AI 생성, 플레이어가 선택하지 않은 영지 중 자신의 영지를 하나 선택
    // 데모를 위해 랜덤으로 하지 않음
    if(initial_state->get_state_id() == Hamgyeongdo) {
        ai->add_state(game.get_states().at(7));
    } else {
        ai->add_state(game.get_states().at(0));
    }

    // users에 player와 ai 업캐스팅해서 추가
    game.add_user(player);
    game.add_user(ai);

    // 시작 플레이어 - 사용자(player)부터 시작한다
    game.set_user_turn(player);

    // 게임 시작
    while(1) { // 게임 종료 조건 넣기

        // 현재 플레이어 설정
        User* current_user = game.get_user_turn();
        cout << "----------------------------\n";
        cout << "현재 턴 : " << current_user->get_user_id() << "\n";

        // 총 턴과 날짜 표시
        cout << "턴 : " << game.get_total_turn() << " , " << "날짜 : " << game.get_date() << "\n";
        
        // 6월, 9월에 농업도에 비례해서 식량 수확 (모든 플레이어가)
        if(game.get_date().find("6월")!= std::string::npos || game.get_date().find("9월")!= std::string::npos) {
            cout << "즐거운 수확철~ 식량이 증가합니다!\n";
            
            // 각 유저에 대해
            vector<User*>::iterator it;

            for(it = game.get_users().begin(); it != game.get_users().end(); it++) {

                cout << "유저들 : " << (*it)->get_total_rice() << "\n";

                vector<State*> user_states = (*it)->get_own_states();
                
                cout << "테스트 : " << user_states.at(0)->get_state_name() << "\n";
                
                cout << "유저들 : " << (*it)->get_total_rice() << "\n";

                vector<State*>::iterator iter;
                int total_gain = 0;

                for(iter = user_states.begin(); iter != user_states.end(); iter++) {
                    total_gain += (*iter)->get_agriculture_degree() * 20;
                }

                cout << (*it)->get_user_id() << "의 획득 식량 " << total_gain << "\n";

                (*it)->increase_total_rice(total_gain);
            }
        }

        if(current_user->get_user_id() == "AI") {
            // AI가 플레이를 진행 중입니다... 과 같은 식으로 메시지가 찍히면서 딜레이??
            // .이 하나하나 찍히면서?
            game.increase_total_turn();;
            game.set_user_turn(game.next_user_turn(current_user));
            continue;
        }

        // 아래는 플레이어 차례에만 진행
        // ... 아래는 나중에 다 함수로 빼자

        cout << "----------------------------\n";
        cout << "현재 식량 : " << current_user->get_total_rice() << "\n";
        cout << "----------------------------\n";

        // 플레이어 명령
        Player *player = static_cast<Player*>(game.get_users().at(0));

        string input_state;
        string input_hero;
        string command;

        State* current_state;
        while(1) {
            cout << "영지를 선택하십시오.\n";
            vector<State*> mystate = player->get_own_states();
            vector<State*>::iterator mystateIter;
            // state_id 순서대로 출력되게 해야하나
            for(mystateIter = mystate.begin(); mystateIter != mystate.end(); mystateIter++) {
                cout << (*mystateIter)->get_state_id() << ". "<< (*mystateIter) -> get_state_name() << "\n";
            }
            cin >> input_state;

            State& select_state = player->find_own_state(static_cast<StateId>(atoi(input_state.c_str())));
            current_state = &select_state;

            cout << "현 도시 농업도 : " << select_state.get_agriculture_degree() << "\n";
            cout << "현 도시 병사들의 훈련도 : " << select_state.get_soldier_degree() << "\n";
            cout << "현 도시 병사수 : " << select_state.get_state_soilder() << "\n";

            cout << "현 영지에서 명령을 하시겠습니까? y/n\n";
            string input;
            cin >> input;
            if(input == "y") break;
        }
        
        cout << "임무를 수행할 영웅을 선택하십시오.\n";
        
        vector<GameUnit> unit_list = current_state->get_unit_list();
        vector<GameUnit>::iterator unitIter;
        for(unitIter = unit_list.begin(); unitIter != unit_list.end(); unitIter++) {
            // 영웅에 대해 '군주'이거나 '등용' 상태이면 보여주기
            if((*unitIter).get_status() == munonarch || (*unitIter).get_status() == developed) {
                string status;
                switch ((*unitIter).get_status())
                {
                    case munonarch:
                        status = "군주";
                        break;
                    case developed:
                        status = "등용";
                        break;
                    default:
                        break;
                }
                cout << (*unitIter).get_name() << " : " << status << "\n";
            }
        }
        // 번호로 부를 수 있게 해야하나 - 영웅 아이디가 없어서 번거로움..
        // 존함을 정자로 입력해주시기 바랍니다!
        cout << "이름 : ";
        cin >> input_hero;

        GameUnit hero;
        for(unitIter = unit_list.begin(); unitIter != unit_list.end(); unitIter++) {
            if(input_hero == (*unitIter).get_name()) {
                hero = *unitIter;   // 얕은 복사해도 괜찮다
            }
        }

        // 이전에 영웅의 행동력을 확인?

        cout << "행동을 선택하십시오.\n";
        cout << "1. 인사 : 탐색(한번) or 등용(한번) or 이동(무제한) 중 한 행동을 할 수 있습니다.\n";
        cout << "2. 내정 : 선택된 영웅의 정치에 비례하여 농업도를 향상\n";
        cout << "3. 병사 : 모집 or 훈련 중 한 행동을 할 수 있습니다.\n";
        cout << "4. 전쟁 : 인접한 적군의 영지를 선택해 공격\n";
        cin >> command;

        string detail_command;
        switch(static_cast<Command>(atoi(command.c_str()))) {
            case HR: // 인사
                cout << "다음 중 행동을 하나 선택하세요.\n";
                cout << "1. 탐색 : 현재 있는 영지의 영웅을 탐색할 수 있는 것으로, 미발견 상태의 인물을 발견하여 재야 상태로 바꾼다.\n";
                cout << "2. 등용 : 탐색으로 발견되어 '재야' 상태이거나, 전쟁에서 진 상대편의 영웅(재야 상태)를 등용할 수 있는 것으로, 매력의 영향을 받는다.\n";
                cout << "3. 이동 : 본인이 등용한 장수를 다른 영지로 이동시킬 수 있다.\n";

                cin >> detail_command;
                switch(atoi(detail_command.c_str())) {
                    case 1: // 탐색
                        player->command(FindUnit, hero);
                        break;
                    case 2: // 등용
                        // player->command(GetUnit, hero, 등용할 영웅);
                        break;
                    case 3: // 이동
                        // player->command(MoveUnit, hero, 이동할 영지);
                        break;
                    default:
                        break;
                }
                break;
            case Politic: // 내정
                player->command(Politic, hero);
                break;
            case Soldier: // 병사
                cout << "다음 중 행동을 하나 선택하세요.\n";
                cout << "1. 모집 : 영웅의 무력에 영향을 받으며 병사를 모집한다.\n";
                cout << "2. 훈련 : 영웅의 통솔에 영향을 받으며 병사를 훈련한다.\n";
                
                cin >> detail_command;
                switch(atoi(detail_command.c_str())) {
                    case 1:
                        //player->command(GetSoldier, hero, 모집할 병사의 수);
                        break;
                    case 2:
                        player->command(TrainSolider, hero);
                        break;
                    default:
                        break;
                }
                break;
            case War: // 전쟁
                //
                break;
            default:
                break;
        }

        cout << input_hero << "의 행동력이 소모됩니다.\n\n";
        hero.set_can_move(false);

        game.increase_total_turn();;
        game.set_user_turn(game.next_user_turn(current_user));
    }

    User *me = game.get_users().at(0);
    
    cout << (me->get_total_rice()) << "\n";
    cout << (me->get_user_id()) << "\n";
    cout << (me->find_own_state(Hamgyeongdo).get_state_name()) << "\n";
    cout << (me->find_own_state(Pyongando).get_state_name()) << "\n";

    // 마지막에 game에서 동적할당된 state 등을 delete 해주기
    // player 들도 동적할당되서 delete 필요

    return 0;
}