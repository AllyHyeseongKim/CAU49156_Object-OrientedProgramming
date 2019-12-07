#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/game_controller.h"

#include <QGraphicsDropShadowEffect>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QLayout>
#include <QSignalMapper>
#include <QString>
#include <iostream>
#include <string>

GameController game;
Player *player;
GameAI *ai;
State *initial_state;
bool turn_continue;
User* current_user;
State *ai_war_states;
State *attacked_state;
GameUnit *war_hero;

QColor black(0,0,0);
QColor transparentBlack(0,0,0,120);
QColor transparentBlue(0,90,200,120);

MainWindow::MainWindow(QWidget *parent): QDialog(parent), ui(new Ui::MainWindow){
    setFilePath();
    initBoard();
    setFixedSize(590, 440);
}

void MainWindow::clickMap(int id){
    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};
    State* current_state;
    State& select_state = player->find_own_state(static_cast<StateId>(id));
    current_state = &select_state;

    setText3(select_state.get_agriculture_degree());
    setText4(select_state.get_state_soilder(), select_state.get_soldier_degree());

    for(QToolButton *button : mapButtons){
        button->setDisabled(true);
        button->setStyleSheet("color: #CCCCCC; border-radius: 10px; background-color: #80000000;");
    }
    vector<State*> mystate = player->get_own_states();
    for(State *state : mystate){
        mapButtons[state->get_state_id() - 1]->setEnabled(true);
        mapButtons[state->get_state_id() - 1]->setStyleSheet("color: #000000; border-radius: 10px; background-color: #A0FFFFFF;");
    }
    mapButtons[id-1]->setStyleSheet("border-radius: 10px;background-color: #007aff;color: white;");

    vector<GameUnit> &unit_list = current_state->get_unit_list();
    vector<GameUnit>::iterator unitIter;
    bool flag = false;

    //행동할 수 있는 유닛 확인
    vector<GameUnit> available_list;
    vector<QString> show_list;

    for(unitIter = unit_list.begin(); unitIter != unit_list.end(); unitIter++){
        if(((*unitIter).get_status() == munonarch || (*unitIter).get_status() == hired) && (*unitIter).get_can_move()) {
            available_list.push_back(*unitIter);
            QString k = QString::fromStdString(unitIter->get_name());
            k = k.append(QString::fromStdString(" : "));
            switch (unitIter->get_status()){
                case munonarch:
                    k = k.append("군주");
                    break;
                case hired:
                    k = k.append("등용");
                    break;
                default:
                    break;
            }
            show_list.push_back(k);
            flag = true;
        }
    }

    if(!flag) {
        show_list = {};
        showAlert("활동할 수 있는 영웅이 없습니다.");
        return;
    }
    else{
        showList(show_list, true);
        showAlert("임무를 수행할 영웅을 선택하십시오.");
    }




//    // 번호로 부를 수 있게 해야하나 - 영웅 아이디가 없어서 번거로움..
//    // 존함을 정자로 입력해주시기 바랍니다!
//    cout << "이름 : ";
//    cin >> input_hero;

//    if (input_hero == "q")
//        continue;

//    GameUnit *hero;
//    for(unitIter = unit_list.begin(); unitIter != unit_list.end(); unitIter++) {
//        if(input_hero == (*unitIter).get_name()) {
//            hero = &(*unitIter);
//        }
//    }

//    if(!hero->get_can_move()) {
//        cout << hero->get_name() << "의 행동력이 부족합니다\n";
//        continue;
//    }

//    // 이전에 영웅의 행동력을 확인?

//    // 여기가 btn1~5 확인하던 곳!!!!!!!!!!!!!!!!

//    // player 전쟁 정보 확인
//    if(aggress_state_id) {
//        GameUnit *ai_unit;
//        aggress_hero->set_can_move(false);

//        if(ai->chk_own_state(aggress_state_id)) {
//            ai_unit = ai->defence_state(*current_state, *game.get_state_by_id(aggress_state_id), *aggress_hero, aggress_num_solider);
//            bool result = current_state->war(*aggress_hero, aggress_num_solider, *game.get_state_by_id(aggress_state_id), *ai_unit);
//            if(result)
//                cout << "공격에 성공했습니다.\n";
//            else
//                cout << "공격에 실패했습니다.\n";
//        }
//        else {
//            State *state = game.get_state_by_id(aggress_state_id);
//            player->add_state(state);
//            state->set_state_owner(player);
//            cout << "공격에 성공했습니다.\n";
//        }
//    }
}
void MainWindow::clickMapActionBtn1(){
//    cout << "다음 중 행동을 하나 선택하세요.\n";
//    cout << "1. 탐색 : 현재 있는 영지의 영웅을 탐색할 수 있는 것으로, 미발견 상태의 인물을 발견하여 재야 상태로 바꾼다.\n";
//    cout << "2. 등용 : 탐색으로 발견되어 '재야' 상태이거나, 전쟁에서 진 상대편의 영웅(재야 상태)를 등용할 수 있는 것으로, 매력의 영향을 받는다.\n";
//    cout << "3. 이동 : 본인이 등용한 장수를 다른 영지로 이동시킬 수 있다.\n";

//    string detail_command;
//    vector<GameUnit> &temp_unit_list = current_state->get_unit_list();
//    cin >> detail_command;

//    switch(atoi(detail_command.c_str())) {
//        case 1: {// 탐색
//            player->command(FindUnit, *hero);
//            break;
//        }
//        case 2: {// 등용
//            int unit_index = 1;
//            int selected_unit_index;
//            int num_develop = 0;
//            vector<GameUnit*> developed_unit;
//            cout << temp_unit_list.size() << endl;


//            for(int i = 0; i < temp_unit_list.size(); i++){
//                if(temp_unit_list[i].get_status() == developed){
//                    num_develop++;
//                }
//            }
//            if (num_develop == 0) {
//                cout << "등용할 영웅이 없습니다.\n";
//                break;
//            }

//            cout << "등용할 영웅을 고르시오\n";

//            for(int i = 0; i < temp_unit_list.size(); i++){
//                if(temp_unit_list[i].get_status() == developed){
//                    cout << unit_index <<':' << temp_unit_list[i].get_name() <<
//                    " 무력: " << temp_unit_list[i].get_strength() << " 통솔: " << temp_unit_list[i].get_leadearship() <<
//                    " 지력: " << temp_unit_list[i].get_wisdom() << "정치: " << temp_unit_list[i].get_political() <<
//                    " 매력: " << temp_unit_list[i].get_attraction() <<  endl;
//                    developed_unit.push_back(&temp_unit_list[i]);
//                    unit_index++;
//                }
//            }
//            cin >> selected_unit_index;
//            unit_index = 1;
//            player->command(GetUnit, *hero, *developed_unit[selected_unit_index - 1]);

//            if(current_state->is_hired(*developed_unit[selected_unit_index - 1]))
//                cout << developed_unit[selected_unit_index - 1]->get_name() <<  "이 등용되었습니다. " << endl;
//            else
//                cout << developed_unit[selected_unit_index - 1]->get_name() <<  "을 등용에 실패하셨습니다. " << endl;

//            break;
//        }
//        case 3: {// 이동
//            std::vector<State*> state_list = player->get_own_states();
//            int selected_index;
//            StateId selected_state_id;
//            cout << "\n 옮길 지역을 입력해주세요.\n";
//            for (int i = 0; i < state_list.size(); i++) {
//                cout << i + 1 << ": " << state_list[i]->get_state_name() << endl;
//            }

//            while(true) {
//                cin >> selected_index;

//                for (int i = 0; i < state_list.size(); i++) {
//                    if(selected_index == i + 1) {
//                        selected_state_id = state_list[i]->get_state_id();
//                    }
//                }

//                if(player->chk_own_state(selected_state_id))
//                    break;
//                cout << "\n 옳바른 지역을 입력해주세요.\n";
//            }

//            player->command(MoveUnit, *hero, selected_state_id);
//            return;
//        }
//    }
//    clickMapActionBtnWrapUp();
}
void MainWindow::clickMapActionBtn2(){
//    player->command(Politic, *hero);
//    clickMapActionBtnWrapUp();
}
void MainWindow::clickMapActionBtn3(){
//    cout << "다음 중 행동을 하나 선택하세요.\n";
//    cout << "1. 모집 : 영웅의 무력에 영향을 받으며 병사를 모집한다.\n";
//    cout << "2. 훈련 : 영웅의 통솔에 영향을 받으며 병사를 훈련한다.\n";

//    cin >> detail_command;
//    switch(atoi(detail_command.c_str())) {
//        int num_soldier;
//        case 1:
//            while (true) {
//                cout << "모집할 병사의 수를 입력하세요\n";
//                cin >> num_soldier;
//                if(num_soldier <= player->get_total_rice())
//                    break;
//                cout << "식량이 부족합니다\n";
//            }
//            player->command(GetSoldier, *hero, num_soldier);
//            break;
//        case 2:
//            player->command(TrainSolider, *hero);
//            break;
//        default:
//            break;
//    }
//    clickMapActionBtnWrapUp();
}
void MainWindow::clickMapActionBtn4(){
//    std::vector<StateId> state_id_list = current_state->get_near_state();
//    std::vector<State*> state_list = game.get_states();
//    vector<GameUnit*> developed_unit;

//    int selected_state;
//    int state_index = 1;
//    bool flag = false;
//    int unit_index = 1;
//    int selected_unit_index;

//    for(int i = 0; i < state_id_list.size(); i++) {
//        if (!player->chk_own_state(state_id_list[i])){
//            cout << state_index << ": " << state_list.at(state_id_list[i] - 1)->get_state_name() << endl;
//            state_index++;
//        }
//    }

//    cin >> selected_state;

//    aggress_num_solider = 0;
//    while(aggress_num_solider > current_state->get_state_soilder()) {
//        cout << "병사의 수를 입력하세요. 최대 유닛: " << current_state->get_state_soilder() << endl;
//        cin >> aggress_num_solider;
//    }

//    cout << "전쟁에 내보낼 영웅을 고르시오\n";

//    for(int i = 0; i < unit_list.size(); i++){
//        if(unit_list[i].get_status() == hired || unit_list[i].get_status() == munonarch){
//            cout << unit_index <<':' << unit_list[i].get_name() <<
//            " 무력: " << unit_list[i].get_strength() << " 통솔: " << unit_list[i].get_leadearship() <<
//            " 지력: " << unit_list[i].get_wisdom() << "정치: " << unit_list[i].get_political() <<
//            " 매력: " << unit_list[i].get_attraction() <<  endl;
//            developed_unit.push_back(&unit_list[i]);
//            unit_index++;
//        }
//    }
//    cin >> selected_unit_index;

//    aggress_hero = developed_unit[selected_unit_index - 1];

//    state_index = 1;
//    for(int i = 0; i < state_id_list.size(); i++) {
//        if (!player->chk_own_state(state_id_list[i])){
//            if(selected_state == state_index) {
//                aggress_state_id = state_id_list[i];
//                aggress_hero = hero;
//            }
//            state_index++;
//        }
//    }
//    clickMapActionBtnWrapUp();
}
void MainWindow::clickMapActionBtnWrapUp(){
//    cout << input_hero << "의 행동력이 소모됩니다.\n\n";
}
void MainWindow::clickMapActionBtn5(){
    game.increase_total_turn();
    game.set_user_turn(game.next_user_turn(current_user));
    gameLoop();
    if(game.check_game_judge() == WIN) {
        // 승리의 간지나는 아스키코드~ㅎㅎ
    }
    if(game.check_game_judge() == LOSE) {
        // 패배를 뼈저리게 느낄만한 아스키코드~
    }
}

void MainWindow::showAlert(QString n){
    ui->alert_label->setText(n);
    ui->alertDialog->raise();
    ui->alertDialog->show();
}
void MainWindow::closeAlert(){
    ui->alertDialog->hide();
}
void MainWindow::showSelection(QString message, QString cancel, QString accept){
    ui->selection_label->setText(message);
    ui->selection_accept_btn->setText(accept);
    ui->selection_cancel_btn->setText(cancel);
    ui->selectionDialog->raise();
    ui->selectionDialog->show();
}
void MainWindow::closeSelectionCancel(){
    ui->selectionDialog->hide();
}
void MainWindow::closeSelectionAccept(){
    ui->selectionDialog->hide();
}
void MainWindow::showList(std::vector<QString> list, bool should_show_back){
    if(should_show_back){
        list.push_back(QString::fromStdString("돌아가기"));
    }

    QVBoxLayout *layout=new QVBoxLayout();
    QSignalMapper* paramMapper = new QSignalMapper (this) ;
    for (QString item : list) {
        QPushButton *button = new QPushButton();
        button->setFixedSize(120,32);
        button->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
        button->setText(item);
        paramMapper -> setMapping (button, item) ;
        connect (paramMapper, SIGNAL(mapped(QString)), this, SLOT(listHero(QString))) ;
        layout->addWidget(button);
    }

    layout->setAlignment(Qt::AlignCenter);
    ui->listDialog->setLayout(layout); // Add the layout to widget!
    ui->listDialog->raise();
    ui->listDialog->show();
}
void MainWindow::closeList(){
    ui->listDialog->hide();
    QPushButton *controlButtons[] = {ui->btn1,ui->btn2,ui->btn3,ui->btn4};
    for(int i=0;i<4;i++){
        controlButtons[i]->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
        controlButtons[i]->setDisabled(true);
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(20);
        effect->setXOffset(0.2);
        effect->setYOffset(0.5);
        effect->setColor(transparentBlue);
        controlButtons[i]->setGraphicsEffect(effect);
    }
}

void MainWindow::listHero(QString value){
    bool flag = false;

    if(!value.compare("돌아가기")){
        closeList();
        return;
    }

    for(GameUnit item : attacked_state->get_unit_list()){
        if(!item.get_name().compare(value.toStdString())){
            war_hero = &item;
            break;
        }
    }

    //참전하는 인공지능 유닛과 병력
    pair<GameUnit*, int> ai_unit = ai->attack_state(*ai_war_states, *attacked_state, *war_hero);
    bool result = attacked_state->defense(*war_hero, *ai_war_states, *ai_unit.first, ai_unit.second);
    if(result)
        showAlert("방어에 성공했습니다.\n");
    else
        showAlert("방어에 실패했습니다.\n");

    ai_war_states = NULL;
    attacked_state = NULL;
    war_hero = NULL;
//    ai_aggress_state_id = 0;
}

void MainWindow::gameInit(){
    ai = new GameAI("AI");
    player->add_state(initial_state);
    initial_state->set_state_owner(player);
    // AI 생성, 플레이어가 선택하지 않은 영지 중 자신의 영지를 하나 선택
    // 데모를 위해 랜덤으로 하지 않음
    if(initial_state->get_state_id() == Hamgyeongdo) {
        ai->add_state(game.get_states().at(7));
        game.get_states().at(7)->set_state_owner(ai);
    } else {
        ai->add_state(game.get_states().at(0));
        game.get_states().at(0)->set_state_owner(ai);
    }

    // users에 player와 ai 업캐스팅해서 추가
    game.add_user(player);
    game.add_user(ai);

    // 시작 플레이어 - 사용자(player)부터 시작한다
    game.set_user_turn(player);
//    std::vector<QString> selectionStrings = {"a", "b"};
//    showList(selectionStrings);


    setText2(player->get_total_rice());

    gameLoop();
}

void MainWindow::gameLoop(){
    // 모든 지역에 있는 유닛들 행동력 회복
    vector<State*> all_state = game.get_states();
    for(int i = 0; i < all_state.size(); i++)
        all_state[i]->reset_can_move();

    // 전쟁시 필요한 정보들
    StateId aggress_state_id = (StateId)0;
    int aggress_num_solider = 0;
    GameUnit *aggress_hero = 0;

    StateId ai_aggress_state_id = (StateId)0;
    int ai_aggress_num_solider = 0;
    GameUnit *ai_aggress_hero = 0;

    // 현재 플레이어 설정
    current_user = game.get_user_turn();
    setText6(game.get_total_turn(), QString::fromStdString(current_user->get_user_id()));

    // 총 턴과 날짜 표시
    setText5(QString::fromStdString(game.get_date()));

    // 6월, 9월에 농업도에 비례해서 식량 수확 (모든 플레이어가)
    if(game.get_date().find("6월")!= std::string::npos || game.get_date().find("9월")!= std::string::npos) {
        // 각 유저에 대해
        vector<User*> users = game.get_users();
        QString finalString;
        for(int i = 0; i < users.size(); i++) {
            vector<State*> user_states = users[i]->get_own_states();
            vector<State*>::iterator iter;
            int total_gain = 0;
            for(iter = user_states.begin(); iter != user_states.end(); iter++) {
                total_gain += (*iter)->get_agriculture_degree() * 20;
            }
            finalString = finalString.append(QString::fromStdString(users[i]->get_user_id())).append(QString::fromStdString("의 식량이 ")).append(QString::fromStdString(std::to_string(total_gain))).append("증가합니다.\n");

            users[i]->increase_total_rice(total_gain);
            setText2(player->get_total_rice());
        }
        showAlert(QString::fromStdString("즐거운 수확철~\n\n").append(finalString));
    }

    if(current_user->get_user_id() == "AI") {
        // AI가 플레이를 진행 중입니다... 과 같은 식으로 메시지가 찍히면서 딜레이??
        // .이 하나하나 찍히면서?

        ai->AI_algo(game.get_total_turn()/2);

//        game.increase_total_turn();
        game.set_user_turn(game.next_user_turn(current_user));
        return;
    }

    if(((int)(game.get_total_turn()/2))%20 == 0 &&  (int)(game.get_total_turn()/2) != 0) {
        // 주변에 자신의 것이 아닌 도시를 찾기
        std::vector<State*> ai_states = ai->get_own_states();
        bool flag = true;
        // 전쟁나갈 인공지능의 도시

        for(int i = 0; i < ai_states.size() && flag; i++) {
            vector<StateId> near_state = ai_states[i]->get_near_state();
            for(int j = 0; i < near_state.size() && flag; j++) {
                if(!ai->chk_own_state(near_state[j])) {
                    ai_aggress_state_id = near_state[j];
                    ai_war_states = ai_states[i];
                    flag = false;
                }
            }
        }

        // 빈 도시인가?

        attacked_state = game.get_state_by_id(ai_aggress_state_id);
        if(!player->chk_own_state(ai_aggress_state_id)) {
            ai->add_state(attacked_state);
            attacked_state->set_state_owner(ai);
        }
        else {


            vector<GameUnit> &unit_list = attacked_state->get_unit_list();
            vector<GameUnit>::iterator unitIter;

            vector<QString> show_list;

            for(unitIter = unit_list.begin(); unitIter != unit_list.end(); unitIter++) {
                if((*unitIter).get_status() == munonarch || (*unitIter).get_status() == hired) {
                    show_list.push_back(QString::fromStdString((*unitIter).get_name()));
                }
            }
            showList(show_list, false);
            showAlert(QString::fromStdString(attacked_state->get_state_name()).append("이 공격당했습니다.\n출전시킬 영웅을 고르세요."));
        }
    }

    Player *player = static_cast<Player*>(game.get_users().at(0));

    string input_state;
    string input_hero;
    string command;

    QPushButton *controlButtons[] = {ui->btn1,ui->btn2,ui->btn3,ui->btn4};
    for(int i=0;i<4;i++){
        controlButtons[i]->setStyleSheet("border-radius: 5px;background-color: #80000000;color: #CCCCCC;");
        controlButtons[i]->setDisabled(true);
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(20);
        effect->setXOffset(0.2);
        effect->setYOffset(0.5);
        effect->setColor(QColor(180,180,180,120));
        controlButtons[i]->setGraphicsEffect(effect);
    }
    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};
    turn_continue = true;
    for(QToolButton *button : mapButtons){
        button->setDisabled(true);
        button->setStyleSheet("color: #CCCCCC; border-radius: 10px; background-color: #80000000;");
    }
    vector<State*> mystate = player->get_own_states();
    for(State *state : mystate){
        mapButtons[state->get_state_id() - 1]->setEnabled(true);
        mapButtons[state->get_state_id() - 1]->setStyleSheet("color: #000000; border-radius: 10px; background-color: #A0FFFFFF;");
    }
}

void MainWindow::initBoard(){
    ui->setupUi(this);

    QPixmap pic("../map.png");
    if(pic.isNull()){
        pic = QPixmap("/Users/herojeff/WorkSpace/OOPS-Project4/map.png");
    }
    QPixmap scaled=pic.scaled ( 291, 371, Qt::KeepAspectRatio, Qt::FastTransformation );
    ui->imageView->setPixmap(scaled);
    ui->imageView->lower();

    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};
    for(int i=0;i<9;i++){
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(5);
        effect->setXOffset(0.2);
        effect->setYOffset(0.5);
        effect->setColor(transparentBlack);
        mapButtons[i]->setGraphicsEffect(effect);
    }

    QPushButton *controlButtons[] = {ui->btn1,ui->btn2,ui->btn3,ui->btn4,ui->btn5,ui->btn_hero_1,ui->btn_hero_2,ui->btn_hero_3,ui->btn_hero_4,ui->btn_id_confirm};
    for(int i=0;i<10;i++){
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(20);
        effect->setXOffset(0.2);
        effect->setYOffset(0.5);
        effect->setColor(transparentBlue);
        controlButtons[i]->setGraphicsEffect(effect);
    }

    ui->id->setAttribute(Qt::WA_MacShowFocusRect,0);

    setText1(0);
    setText2(0);
    setText3(0);
    setText4(0, 0);
    setText5("");
    setText6(0, "");

    ui->buttonGrid->hide();
    ui->container2->hide();
    ui->container3->hide();
    ui->container5->hide();
    ui->alertDialog->hide();
    ui->selectionDialog->hide();
    ui->listDialog->hide();


//    connect(ui->id,  SIGNAL(returnPressed()),ui->btn_id_confirm,SIGNAL(released()));
    connect(ui->btn_id_confirm, SIGNAL(released()),this, SLOT(setUserID()));
    connect(ui->btn_hero_1, SIGNAL(released()),this, SLOT(setHero1()));
    connect(ui->btn_hero_2, SIGNAL(released()),this, SLOT(setHero2()));
    connect(ui->btn_hero_3, SIGNAL(released()),this, SLOT(setHero3()));
    connect(ui->btn_hero_4, SIGNAL(released()),this, SLOT(setHero4()));

    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect(ui->map1, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map2, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map3, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map4, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map5, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map6, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map7, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map8, SIGNAL(released()),signalMapper, SLOT(map()));
    connect(ui->map9, SIGNAL(released()),signalMapper, SLOT(map()));
    signalMapper -> setMapping (ui->map1, 1) ;
    signalMapper -> setMapping (ui->map2, 2) ;
    signalMapper -> setMapping (ui->map3, 3) ;
    signalMapper -> setMapping (ui->map4, 4) ;
    signalMapper -> setMapping (ui->map5, 5) ;
    signalMapper -> setMapping (ui->map6, 6) ;
    signalMapper -> setMapping (ui->map7, 7) ;
    signalMapper -> setMapping (ui->map8, 8) ;
    signalMapper -> setMapping (ui->map9, 9) ;
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(clickMap(int))) ;

    connect(ui->btn1, SIGNAL(released()),this, SLOT(clickMapActionBtn1()));
    connect(ui->btn2, SIGNAL(released()),this, SLOT(clickMapActionBtn2()));
    connect(ui->btn3, SIGNAL(released()),this, SLOT(clickMapActionBtn3()));
    connect(ui->btn4, SIGNAL(released()),this, SLOT(clickMapActionBtn4()));
    connect(ui->btn5, SIGNAL(released()),this, SLOT(clickMapActionBtn5()));

    connect(ui->alert_btn, SIGNAL(released()),this, SLOT(closeAlert()));
    connect(ui->selection_cancel_btn, SIGNAL(released()),this, SLOT(closeSelectionCancel()));
    connect(ui->selection_accept_btn, SIGNAL(released()),this, SLOT(closeSelectionAccept()));
    connect(ui->selection_accept_btn, SIGNAL(released()),this, SLOT(closeSelectionAccept()));
}

bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void MainWindow::setFilePath(){
    if(!fileExists("data/game_state_data.txt")){
        game.set_states("/Users/herojeff/WorkSpace/OOPS-Project4/data/game_state_data.txt");
    }
    else{
        game.set_states("data/game_state_data.txt");    // 나중에 set_user와 합쳐서 set_game으로 발전?
    }
}

void MainWindow::setUserID(){
    string user_id;
    user_id = ui->id->text().toStdString();
    if(user_id.compare("")){
        player = new Player(user_id);
        ui->container4->hide();
        ui->container5->show();
    }
}
void MainWindow::setHero(){
    ui->container5->hide();
    ui->container2->show();
    ui->container3->show();
    ui->buttonGrid->show();
    gameInit();
}
void MainWindow::setHero1(){
    showAlert(QString("이성계를 선택했습니다!\n함경도에서 시작합니다!"));
    initial_state = game.get_states().at(0);
    setHero();
}
void MainWindow::setHero2(){
    showAlert(QString("견훤을 선택했습니다!\n전라도에서 시작합니다!"));
    initial_state = game.get_states().at(7);
    setHero();
}
void MainWindow::setHero3(){
    showAlert(QString("문무왕을 선택했습니다!\n경상도에서 시작합니다!"));
    initial_state = game.get_states().at(6);
    setHero();
}
void MainWindow::setHero4(){
    showAlert(QString("고려 광종을 선택했습니다!\n황해도에서 시작합니다!"));
    initial_state = game.get_states().at(3);
    setHero();
}

void MainWindow::setText1(int a){
    QString final = "현재 금 : ";
    final = final.append(QString::number(a));
    ui->label1->setText(final);
}
void MainWindow::setText2(int a){
    QString final = "현재 식량 : ";
    final = final.append(QString::number(a));
    ui->label2->setText(final);
}
void MainWindow::setText3(int a){
    QString final = "현재 도시 농업 : ";
    final = final.append(QString::number(a));
    ui->label3->setText(final);
}
void MainWindow::setText4(int a, int b){
    QString final = "현재 도시 병사 수 / 훈련도 : ";
    final = final.append(QString::number(a));
    final = final.append(" / ");
    final = final.append(QString::number(b));
    ui->label4->setText(final);
}
void MainWindow::setText5(QString a){
    QString final = "날짜 : ";
    final = final.append(a);
    ui->label5->setText(final);
}
void MainWindow::setText6(int a, QString name){
    QString final = QString("현재 턴 : ").append(QString::number(a)).append(", ").append(name);
    ui->label6->setText(final);
}

MainWindow::~MainWindow()
{
    delete ui;
}
