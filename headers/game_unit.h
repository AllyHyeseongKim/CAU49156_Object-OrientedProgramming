#ifndef GAME_UNIT_H
#define GAME_UNIT_H

#include <string>
using namespace std;

typedef enum {undeveloped, developed, hired, munonarch} UnitStatus;

class GameUnit {
    std::string name;
    int strength;       // 무력
    int leadership;     // 통솔
    int wisdom;         // 지력
    int political;      // 정치
    int attraction;     // 매력
    UnitStatus status;  // 탐색으로 찾아내기 전: 미발견, 재야, 등용, 군주

    bool can_move;      // 행동력

public:

    // constructor
    GameUnit(std::string name, int strength, int leadership, int wisdom, int political, int attraction, UnitStatus status);

    // getter
    std::string get_name() const;
    int get_strength() const;
    int get_leadearship() const;
    int get_wisdom() const;
    int get_political() const;
    int get_attraction() const;
    UnitStatus get_status() const;
    bool get_can_move() const;

    // setter
    void set_strength(int strength);
    void set_leadership(int leadership);
    void set_wisdom(int wisdom);
    void set_political(int political);
    void set_attraction(int strength);
    void set_status(UnitStatus status);
    void set_can_move(bool can_move);

    friend bool operator==(GameUnit& unit1, GameUnit& unit2);
    
private:
    // void set_unit();
};

#endif
