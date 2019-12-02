#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <fstream>
#include <sstream>
#include <map>

// #include <boost/tokenizer.hpp>

#include "player.h"
// using namespace boost;

// typedef tokenizer<char_seperator<char>> TOKC;

class GameController {
    
    string player_turn;             // 현재 차례인 유저의 아이디를 저장
    int total_turn;                 // 게임 진행 총 턴 횟수

    vector<Player*> player_list;     // 게임에 참여한 유저 목록
    vector<State*> states;           // 게임의 영지 목록

    string game_state_file;

public:
    
    GameController();

    bool chk_player_turn();
    bool chk_war_win();
    int chk_total_win();
    void increase_total_turn();
    void increase_total_rice();

    // 게임 영지 초기화 - 후에 set_game이 생기면 private으로
    void set_state(string game_state_file);

private:

    void game_data_file_read();
};

#endif