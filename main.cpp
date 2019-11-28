#include "headers/game_controller.h"
#include "headers/game_ai.h"
#include "headers/player.h"

int main(int argc, char *argv[]) {

    vector<State> states;
    GameController game;
    // states = 
    game.set_state("data/game_state_data.txt");
    // 나중에 set_user와 합쳐서 set_game으로 발전?
    return 0;
}