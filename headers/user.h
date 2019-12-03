#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

#include "state.h"

// class State;
// 상호 참조를 전방선언으로 해결하려면, typedef 때문에 user.h 에서는 StateId를 사용하지 않도록 한다 -> State& 로 대체

class User {
protected:
    std::string user_id;                        // 유저 아이디
    std::vector<State*> own_states;             // 유저가 소유한 영지 목록
    int total_rice;                             // 식량, 5000으로 시작

public:
    User(std::string user_id);
    
    bool chk_own_state(StateId state_id);           // 특정 영지가 본인 영지인지 확인?
    State& find_own_state(StateId state_id);         // 영지 이동, chk_own_state와 연관

    // vector<State> get_own_states();             // 현재 유저가 갖고 있는 영지 목록 반환, GUI에서 영지 표시용?
    
    // 유저가 소유한 영지 추가
    void add_state(State* state);

    std::string get_user_id();
    vector<State*> get_own_states();
    int get_total_rice();

    void set_total_rice(int rice);
    void increase_total_rice(int rice);

private:
};

#endif