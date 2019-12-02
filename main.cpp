#include "headers/game_controller.h"
#include "headers/game_ai.h"
#include "headers/player.h"

int main(int argc, char *argv[]) {

    vector<State> states;
    GameController game;
    // states = 
    game.set_state("data/game_state_data.txt");
    // 나중에 set_user와 합쳐서 set_game으로 발전?

    // 게임에 참가한 User들 initial하고 영웅 선택하게 한 후에 game에 저장된 vector<State>에서 가져와 연결

    // 마지막에 game에서 동적할당된 state 등을 delete 해주기
    return 0;
}