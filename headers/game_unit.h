#ifndef GAME_UNIT_H
#define GAME_UNIT_H

#include<string>
using namespace std;

class GameUnit {

    int strength;       // 무력
    int leadership;     // 통솔
    int wisdom;         // 지력
    int political;      // 정치
    int attraction;     // 매력
    bool can_move;      // 행동력

    string status;      // 탐색으로 찾아내기 전: 미발견, 재야, 군주

public:
    int get_strength();
    int get_leadearship();    
    int get_wisdom();
    int get_political();
    int get_attraction();
    
    void set_strength(int strength);
    void set_leadership(int leadership);
    void set_wisdom(int wisdom);
    void set_political(int political);
    void set_attraction(int strength);

private:
    
};

#endif