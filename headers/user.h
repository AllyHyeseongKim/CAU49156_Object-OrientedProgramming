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
    // User 객체를 생성하는 동시에 선택한 초기 영지의 state_id를 own_states에 추가해준다.
    User(std::string user_id, State *state);
    
    State& find_own_state(StateId state_id);         // 영지 이동, chk_own_state와 연관

    // vector<State> get_own_states();             // 현재 유저가 갖고 있는 영지 목록 반환, GUI에서 영지 표시용?
    
    int get_total_rice();
    void set_total_rice(int rice);

private:
    bool chk_own_state(StateId state_id);           // 특정 영지가 본인 영지인지 확인?
};

#endif