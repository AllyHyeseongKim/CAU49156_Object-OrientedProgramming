#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "user.h";

class GameController {
    
    string player_turn;             // 현재 차례인 유저의 아이디를 저장
    int total_turn;                 // 게임 진행 총 턴 횟수
    vector<User> user_list;         // 게임에 참여한 유저 목록

public:
    bool chk_player_turn();
    bool chk_war_win();
    int chk_total_win();
    void increase_total_turn();
    void increase_total_rice();

private:

};

#endif