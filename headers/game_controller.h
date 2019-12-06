#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <fstream>
#include <sstream>
#include <map>

#include "player.h"
#include "game_ai.h"

typedef enum {WIN, LOSE, NOTHING} Judge;

class GameController {
    
    User* user_turn;                 // 현재 차례인 유저의 아이디를 저장
    int total_turn;                 // 게임 진행 총 턴 횟수, 월 단위

    vector<User*> users;            // 게임에 참여한 유저 목록 - 0: 플레이어, 1: AI
    vector<State*> states;          // 게임의 영지 목록

    string game_state_file;

public:
    
    GameController();
    // ~GameController();          // users, states delete 해주기

    User* get_user_turn();
    int get_total_turn();
    string get_date();              // total_turn::int에 따라 YYYY/MM 형식으로 string이 반환
    vector<User*> get_users();
    vector<State*> get_states();

    void set_user_turn(User* user);
    // 게임 영지 초기화 - 후에 set_game이 생기면 private으로
    void set_states(string game_state_file);
    // 플레이어 및 AI 추가
    void add_user(User* user);

    // 현재 플레이어를 넣으면 다음 턴 플레이어를 반환, (일대일 뿐만 아니라 여러 명이 플레이하는 경우도 커버)
    User* next_user_turn(User* user);

    bool chk_player_turn();
    bool chk_war_win();
    int chk_total_win();
    void increase_total_turn();

    State *get_state_by_id(StateId id);

    Judge check_game_judge();

private:
    // void game_data_file_read();
};

#endif