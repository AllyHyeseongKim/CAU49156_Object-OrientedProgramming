#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<vector>

#include "game_unit.h"

class State {
    User state_owner;               // 해당 영지의 주인인 플레이어
    vector<GameUnit> unit_list;     // 해당 영지에 있는 영웅들
    vector<State> near_state;
    int state_id;                   // 1: 함경도, 2: 평안도, 3: 강원도, 4: 황해도, 5: 경기도, 6: 충청도, 7: 경상도, 8: 전라도, 9: 제주도
    int agriculture_degree;         // 현 영지의 농업도, 처음에 모든 영지는 100의 농업도로 초기화
    int soldier_degree;             // 현 영지의 병사들의 훈련도, 모집한 직후에 20으로 시작
    int state_soldier;              // 현 영지의 병사수

public:
    
    // 내정 --------------------------------------------------------------------
    // 정치에 비례하여 농업도 향상
    // 영웅을 한 명 선택하여 일을 맡길 수 있고, 일을 시킨 이후에는 행동력을 다 소모한 것으로 판단, 다른 일을 시킬 수 없다
    // 오직 6월, 9월에 영지 농업도 * 20만큼의 식량이 증가
    // ------------------------------------------------------------------------
    void agriculture(GameUnit selected_unit);

    // 병사 --------------------------------------------------------------------
    // 영웅의 행동력 소모는 위와 마찬가지
    // ------------------------------------------------------------------------
    void recurit_soldier(GameUnit selected_unit, int soldier);          // 모집
    void train_soldier(GameUnit selected_unit);                         // 훈련
    
    // 인사 --------------------------------------------------------------------
    // 인사는 기본적으로 탐색, 등용, 이동으로 이루어짐
    // 이동은 한 턴에 무제한, 탐색과 등용은 한 번만 (플레이어가 본인의 영웅을 선택하여 일을 시킴 - hiring_unit, selected_unit)
    // 영웅의 행동력 소모는 위와 마찬가지
    // ------------------------------------------------------------------------
    // 탐색 : 현재 있는 영지의 영웅을 탐색할 수 있는 것으로, 미발견 상태의 인물을 발견하여 재야 상태로 바꾼다. 
    // 등용 : 탐색으로 발견되어 '재야' 상태이거나, 전쟁에서 진 상대편의 영웅(재야 상태)를 등용할 수 있는 것으로, 매력의 영향을 받는다.
    // 이동 : 본인이 등용한 장수를 다른 영지로 이동시킬 수 있다. 
    void search_unit(GameUnit selected_unit);                           // 탐색
    void hire_unit(GameUnit hiring_unit, GameUnit hired_unit);          // 등용
    void move_unit(GameUnit selected_unit, int moved_state_id);         // 이동

    // 전쟁 --------------------------------------------------------------------
    // 영지를 전부 점령하면 승리
    // 인접한 영지만 공격 가능하다
    // ------------------------------------------------------------------------
    void war(GameUnit selected_unit, int soldier, State attack_state);  // 침략
    void defense(GameUnit selected_unit);                               // 방어
    
    void lose_the_war();

private:

};

#endif