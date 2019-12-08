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
#include <cstring>
#include <QIntValidator>

GameController game;
Player *player;
GameAI *ai;
State *initial_state;
bool turn_continue;
User* current_user;
State *ai_war_states;
State *attacked_state;
GameUnit *war_hero;
State* current_state;
GameUnit *hero = NULL;
QVBoxLayout *showListLayout;
vector<GameUnit*> dev_list;
vector<QString> dev;
int aggress_num_solider = 0;
GameUnit* aggress_hero;
int current_soldier_count = 0;
int current_soldier_degree = 0;
StateId aggress_state_id = (StateId)0;

int clickMapParam = 0;

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

    if(clickMapParam==0){
        State& select_state = player->find_own_state(static_cast<StateId>(id));
        current_state = &select_state;

        setText3(select_state.get_agriculture_degree());
        setText4(select_state.get_state_soilder(), select_state.get_soldier_degree());
        current_soldier_count = select_state.get_state_soilder();
        current_soldier_degree = select_state.get_soldier_degree();

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
                flag = true;
                break;
            }
        }

        if(!flag) {
            showAlert("활동할 수 있는 영웅이 없습니다.");
        }

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
            showList(show_list, true, 2);
            showAlert("임무를 수행할 영웅을 선택하십시오.");
        }
    }
    else if(clickMapParam==1){
        State& select_state = player->find_own_state(static_cast<StateId>(id));
        current_state = &select_state;

        player->command(MoveUnit, *hero, id);
        showAlert("이동 완료");
    }
    else if(clickMapParam==2){
        int originalPosition = current_state->get_state_id();
//        State& select_state = player->find_own_state(static_cast<StateId>(id));
//        current_state = &select_state;

    //    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};
    //    for(QToolButton *button : mapButtons){
    //        button->setDisabled(true);
    //        button->setStyleSheet("color: #CCCCCC; border-radius: 10px; background-color: #80000000;");
    //    }
    //    vector<State*> mystate = player->get_own_states();
    //    for(State *state : mystate){
    //        mapButtons[state->get_state_id() - 1]->setEnabled(true);
    //        mapButtons[state->get_state_id() - 1]->setStyleSheet("color: #000000; border-radius: 10px; background-color: #A0FFFFFF;");
    //    }


        showInputDialog(to_string(current_state->get_state_soilder()).append("명 중 얼마의 병사를 이끄시겠습니까?"), 0);
    }

    clickMapParam=0;
}
void MainWindow::disconnectMap(){
    ui->map1->disconnect();
    ui->map2->disconnect();
    ui->map3->disconnect();
    ui->map4->disconnect();
    ui->map5->disconnect();
    ui->map6->disconnect();
    ui->map7->disconnect();
    ui->map8->disconnect();
    ui->map9->disconnect();
}

void MainWindow::clickMapActionBtn1(){
    if(!hero->get_can_move()) {
        QString final = QString::fromStdString(hero->get_name());
        final.append("의 행동력이 부족합니다");
        showAlert(final);
        return;
    }

    vector<QString> v = {"탐색", "등용", "이동", "현재 있는 영지의 영웅을 탐색할 수 있는 것으로, 미발견 상태의 인물을 발견하여 재야 상태로 바꾼다.", "탐색으로 발견되어 '재야' 상태이거나, 전쟁에서 진 상대편의 영웅(재야 상태)를 등용할 수 있는 것으로, 매력의 영향을 받는다.", "본인이 등용한 장수를 다른 영지로 이동시킬 수 있다."};
    showList(v, true, 0);
}
void MainWindow::clickMapActionBtn2(){
    if(!hero->get_can_move()) {
        QString final = QString::fromStdString(hero->get_name());
        final.append("의 행동력이 부족합니다");
        showAlert(final);
        return;
    }
    player->command(Politic, *hero);
    setText3(current_state->get_agriculture_degree());
    clickMapActionBtnWrapUp(true);
}
void MainWindow::clickMapActionBtn3(){
    if(!hero->get_can_move()) {
        QString final = QString::fromStdString(hero->get_name());
        final.append("의 행동력이 부족합니다");
        showAlert(final);
        return;
    }
    showSelection("1. 모집 : 영웅의 무력에 영향을 받으며 병사를 모집한다.\n\n2. 훈련 : 영웅의 통솔에 영향을 받으며 병사를 훈련한다.", "모집", "훈련");
}
void MainWindow::clickMapActionBtn4(){
    if(!hero->get_can_move()) {
        QString final = QString::fromStdString(hero->get_name());
        final.append("의 행동력이 부족합니다");
        showAlert(final);
        return;
    }

    showAlert("침공 지역을 선택하세요.");
    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};

    std::vector<StateId> state_id_list = current_state->get_near_state();
    std::vector<State*> state_list = game.get_states();
    vector<GameUnit*> developed_unit = {};
    int state_index = 1;

    for(QToolButton *button : mapButtons){
        button->setDisabled(true);
        button->setStyleSheet("color: #CCCCCC; border-radius: 10px; background-color: #80000000;");
    }

    for(int i = 0; i < state_id_list.size(); i++) {
        if (!player->chk_own_state(state_id_list[i])){
            mapButtons[i]->setEnabled(true);
            mapButtons[i]->setStyleSheet("color: #000000; border-radius: 10px; background-color: #A0FFFFFF;");
        }
    }
    clickMapParam=2;
}
void MainWindow::clickMapActionBtnWrapUp(bool shouldShowDone){
    if(shouldShowDone){
        QString final = QString::fromStdString(hero->get_name());
        final = final.append("의 행동력이 소모됩니다.");
        showAlert(final);
    }
    closeList(false);
    // player 전쟁 정보 확인
    // 전쟁시 필요한 정보들
    StateId aggress_state_id = (StateId)0;

    if(aggress_state_id) {
        GameUnit *ai_unit;
        aggress_hero->set_can_move(false);

        if(ai->chk_own_state(aggress_state_id)) {
            ai_unit = ai->defence_state(*current_state, *game.get_state_by_id(aggress_state_id), *aggress_hero, aggress_num_solider);
            bool result = current_state->war(*aggress_hero, aggress_num_solider, *game.get_state_by_id(aggress_state_id), *ai_unit);
            if(result)
                showAlert("공격에 성공했습니다.");
            else
                showAlert("공격에 실패했습니다.");
        }
        else {
            State *state = game.get_state_by_id(aggress_state_id);
            player->add_state(state);
            state->set_state_owner(player);
            showAlert("공격에 성공했습니다.");
        }
    }
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
void MainWindow::showInputDialog(string title, int mode){
    ui->input_label->setText(QString::fromStdString(title));
    ui->inputDialog->show();

    switch (mode){
    case 0:{//전쟁
        ui->input_accept_btn->hide();
        ui->input_accept_war_btn->show();
        break;
    }
    case 1:{//모집할 병사 수
        ui->input_accept_btn->show();
        ui->input_accept_war_btn->hide();
        break;
    }

    }
}
void MainWindow::closeInputDialogWar(){
    string result = ui->line_edit->text().toStdString();
    char cstr[result.size() + 1];
    strcpy(cstr, result.c_str());
    int number = std::atoi(cstr);

    if(number > current_state->get_state_soilder() || number < 0){
        ui->line_edit->setText("");
        showAlert("병사 수가 정상적이지 않습니다.");
    }
    else{
        dev = {};
        ui->inputDialog->hide();
        ui->line_edit->setText("");
        aggress_num_solider = number;

        //todo
        vector<QString> show_list;

        vector<GameUnit> &unit_list = current_state->get_unit_list();
        std::vector<StateId> state_id_list = current_state->get_near_state();
        std::vector<State*> state_list = game.get_states();
        vector<GameUnit*> developed_unit;

        for(int i = 0; i < unit_list.size(); i++){
            if(unit_list[i].get_status() == hired || unit_list[i].get_status() == munonarch){
                show_list.push_back(QString::fromStdString(unit_list[i].get_name()));
                dev.push_back(QString::fromStdString(unit_list[i].get_name()));
                string toolTipText = "무력: ";
                toolTipText = toolTipText.append(to_string(unit_list[i].get_strength()));
                toolTipText = toolTipText.append("\n통솔: ");
                toolTipText = toolTipText.append(to_string(unit_list[i].get_leadearship()));
                toolTipText = toolTipText.append("\n지력: ");
                toolTipText = toolTipText.append(to_string(unit_list[i].get_wisdom()));
                toolTipText = toolTipText.append("\n정치: ");
                toolTipText = toolTipText.append(to_string(unit_list[i].get_political()));
                toolTipText = toolTipText.append("\n매력: ");
                toolTipText = toolTipText.append(to_string(unit_list[i].get_attraction()));
                dev.push_back(QString::fromStdString(toolTipText));
                developed_unit.push_back(&unit_list[i]);
            }

        }

        showList(dev, false, 4);
        showAlert("전쟁에 내보낼 영웅을 고르세요.");
    }
}

void MainWindow::closeInputDialogRecruit(){
    string result = ui->line_edit->text().toStdString();
    char cstr[result.size()+1];
    strcpy(cstr, result.c_str());
    int num_soldier = std::atoi(cstr);

    current_soldier_count += num_soldier;
    setText4(current_soldier_count, current_soldier_degree);

    if(num_soldier > player->get_total_rice()){
        ui->line_edit->setText("");
        showAlert("식량이 부족합니다.");
    }
    else{
        ui->inputDialog->hide();
        ui->line_edit->setText("");
        player->command(GetSoldier, *hero, num_soldier);
        clickMapActionBtnWrapUp(true);
    }


}
void MainWindow::showSelection(QString message, QString cancel, QString accept){
    ui->selection_label->setText(message);
    ui->selection_accept_btn->setText(accept);
    ui->selection_cancel_btn->setText(cancel);
    ui->selectionDialog->raise();
    ui->selectionDialog->show();
}
void MainWindow::selectionRecruitA(){
    closeSelectionAccept();
    hero->set_can_move(true);
    if(!hero->get_can_move()) {
        showAlert(QString::fromStdString(hero->get_name()).append("의 행동력이 부족합니다"));
        return;
    }
    else{
        player->command(TrainSolider, *hero);
        clickMapActionBtnWrapUp(true);
    }
}
void MainWindow::selectionRecruitC(){
    closeSelectionCancel();
    showInputDialog("모집할 병사의 수를 입력하세요.", 1);
}
void MainWindow::closeSelectionCancel(){
    ui->selectionDialog->hide();
}
void MainWindow::closeSelectionAccept(){
    ui->selectionDialog->hide();
}
void MainWindow::showList(std::vector<QString> list, bool should_show_back, int mode){
    if(should_show_back){
        list.push_back(QString::fromStdString("돌아가기"));
    }

    showListLayout = new QVBoxLayout();
    QSignalMapper* paramMapper = new QSignalMapper (this);
    switch(mode){
    case 0: {//hard_code
        QPushButton *button1 = new QPushButton();
        QPushButton *button2 = new QPushButton();
        QPushButton *button3 = new QPushButton();
        button1->setFixedSize(120,32);
        button2->setFixedSize(120,32);
        button3->setFixedSize(120,32);
        button1->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
        button2->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
        button3->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
        button1->setText(list[0]);
        button1->setToolTip(list[3]);
        button2->setText(list[1]);
        button2->setToolTip(list[4]);
        button3->setText(list[2]);
        button3->setToolTip(list[5]);
        connect(button1, SIGNAL(released()),this, SLOT(hardHR1()));
        connect(button2, SIGNAL(released()),this, SLOT(hardHR2()));
        connect(button3, SIGNAL(released()),this, SLOT(hardHR3()));
        showListLayout->addWidget(button1);
        showListLayout->addWidget(button2);
        showListLayout->addWidget(button3);
        break;
    }
    case 1:{//war incoming
        for (QString item : list) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(120,32);
            button->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
            button->setText(item);
            paramMapper->setMapping(button, item);
            connect(button, SIGNAL(released()),paramMapper, SLOT(map()));
            showListLayout->addWidget(button);
        }
        connect(paramMapper, SIGNAL(mapped(QString)), this, SLOT(listDefenceHero(QString)));
        break;
    }
    case 2:{//default hero selector
        for (QString item : list) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(120,32);
            button->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
            button->setText(item);
            paramMapper->setMapping(button, item);
            connect(button, SIGNAL(released()),paramMapper, SLOT(map()));
            showListLayout->addWidget(button);
        }
        connect(paramMapper, SIGNAL(mapped(QString)), this, SLOT(listHero(QString)));
        break;
    }
    case 3:{//등용할 영웅
        for(int i=0;i<list.size();i+=2){
            QPushButton *button = new QPushButton();
            button->setFixedSize(120,32);
            button->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
            button->setText(list[i]);
            button->setToolTip(list[i+1]);
            paramMapper->setMapping(button, list[i]);
            connect(button, SIGNAL(released()),paramMapper, SLOT(map()));
            showListLayout->addWidget(button);
        }
        connect(paramMapper, SIGNAL(mapped(QString)), this, SLOT(listHero1(QString)));
        closeList(false);
        break;
    }
    case 4:{//todo : 전쟁에 참여할 영웅
        for(int i=0;i<list.size();i+=2){
            QPushButton *button = new QPushButton();
            button->setFixedSize(120,32);
            button->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
            button->setText(list[i]);
            button->setToolTip(list[i+1]);
            paramMapper->setMapping(button, list[i]);
            connect(button, SIGNAL(released()),paramMapper, SLOT(map()));
            showListLayout->addWidget(button);
        }
        connect(paramMapper, SIGNAL(mapped(QString)), this, SLOT(listHero2(QString)));
        break;
        }
    }

    showListLayout->setAlignment(Qt::AlignCenter);
    ui->listDialog->setLayout(showListLayout); // Add the layout to widget!
    ui->listDialog->raise();
    ui->listDialog->show();
}
void MainWindow::listHero2(QString value){
    std::vector<StateId> state_id_list = current_state->get_near_state();
    std::vector<State*> state_list = game.get_states();

    for(int i = 0; i < state_id_list.size(); i++) {
        if (!player->chk_own_state(state_id_list[i])){
            aggress_state_id = state_id_list[i];
            aggress_hero = hero;
        }
    }

//    int state_index = 1;
//    for(int i = 0; i < state_id_list.size(); i++) {
//        if (!player->chk_own_state(state_id_list[i])){
//            if(current_state->get_state_id() == state_index) {
//                aggress_state_id = state_id_list[i];
//                aggress_hero = hero;
//            }
//        }
//    }
    closeList(false);
}
void MainWindow::hardHR1(){
    player->command(FindUnit, *hero);
    clickMapActionBtnWrapUp(true);
}
void MainWindow::hardHR2(){
    vector<GameUnit> &temp_unit_list = current_state->get_unit_list();
    int unit_index = 1;
    int selected_unit_index;
    int num_develop = 0;
    vector<GameUnit*> developed_unit;
    cout << temp_unit_list.size() << endl;

    for(int i = 0; i < temp_unit_list.size(); i++){
        if(temp_unit_list[i].get_status() == developed){
            num_develop++;
        }
    }
    if (num_develop == 0) {
        showAlert("등용할 영웅이 없습니다.");
        return;
    }

    //todo
    dev = {};
    dev_list = {};
    for(int i = 0; i < temp_unit_list.size(); i++){
        if(temp_unit_list[i].get_status() == developed){
            dev.push_back(QString::fromStdString(temp_unit_list[i].get_name()));
            string toolTipText = "무력: ";
            toolTipText = toolTipText.append(to_string(temp_unit_list[i].get_strength()));
            toolTipText = toolTipText.append("\n통솔: ");
            toolTipText = toolTipText.append(to_string(temp_unit_list[i].get_leadearship()));
            toolTipText = toolTipText.append("\n지력: ");
            toolTipText = toolTipText.append(to_string(temp_unit_list[i].get_wisdom()));
            toolTipText = toolTipText.append("\n정치: ");
            toolTipText = toolTipText.append(to_string(temp_unit_list[i].get_political()));
            toolTipText = toolTipText.append("\n매력: ");
            toolTipText = toolTipText.append(to_string(temp_unit_list[i].get_attraction()));
            dev.push_back(QString::fromStdString(toolTipText));
            dev_list.push_back(&temp_unit_list[i]);
        }
    }



    showList(dev, false, 3);


}
void MainWindow::hardHR3(){
    showAlert("옮길 지역을 입력해주세요.");
    closeList(false);
    QToolButton *mapButtons[] = {ui->map1,ui->map2,ui->map3,ui->map4,ui->map5,ui->map6,ui->map7,ui->map8,ui->map9};

    disconnectMap();
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
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT((int)));

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
void MainWindow::closeList(bool success){
    ui->listDialog->hide();
    if(success){
        QPushButton *controlButtons[] = {ui->btn1,ui->btn2,ui->btn3,ui->btn4};
        for(int i=0;i<4;i++){
            controlButtons[i]->setStyleSheet("border-radius: 5px;background-color: #007aff;color: white;");
            controlButtons[i]->setEnabled(true);
            QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
            effect->setBlurRadius(20);
            effect->setXOffset(0.2);
            effect->setYOffset(0.5);
            effect->setColor(transparentBlue);
            controlButtons[i]->setGraphicsEffect(effect);
        }
    }
    for (QObject *item : ui->listDialog->children()){
        delete item;
    }
}

void MainWindow::listDefenceHero(QString value){
    if(!value.compare("돌아가기")){
        closeList(false);
        return;
    }

    string str = value.toStdString();
    char cstr[str.size() + 1];
    strcpy(cstr, str.c_str());
    char *token = std::strtok(cstr, " ");
    token = std::strtok(cstr, " ");
    string firstWord = std::strtok(cstr, " :");

    for(GameUnit item : attacked_state->get_unit_list()){
        if(!item.get_name().compare(firstWord)){
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

void MainWindow::listHero(QString value){
    if(!value.compare("돌아가기")){
        closeList(false);
        return;
    }

    string str = value.toStdString();
    char cstr[str.size() + 1];
    strcpy(cstr, str.c_str());
    char *token = std::strtok(cstr, " ");
    token = std::strtok(cstr, " ");
    string firstWord = std::strtok(cstr, " :");

    vector<GameUnit> &unit_list = current_state->get_unit_list();
    vector<GameUnit>::iterator unitIter;
    for(GameUnit &unit : unit_list){
        if(!unit.get_name().compare(firstWord)) {
            hero = &unit;
            closeList(true);
            return;
        }
    }

    if(!hero->get_can_move()) {
        showAlert(QString::fromStdString(hero->get_name()).append("의 행동력이 부족합니다"));
        return;
    }
}

void MainWindow::listHero1(QString value){
    if(!value.compare("돌아가기")){
        closeList(false);
        return;
    }

    string str = value.toStdString();
    char cstr[str.size() + 1];
    strcpy(cstr, str.c_str());
    char *token = std::strtok(cstr, " ");
    token = std::strtok(cstr, " ");
    string firstWord = std::strtok(cstr, " :");


    int i;
    for(i=0;i<dev_list.size();i++){
        if(!dev_list[i]->get_name().compare(firstWord)){
            break;
        }
    }

    player->command(GetUnit, *hero, *dev_list[i]);

    string final;
    if(current_state->is_hired(*dev_list[i])){
        final = dev_list[i]->get_name();
        final = final.append("이(가) 등용되었습니다.");
    }
    else{
        final = dev_list[i]->get_name();
        final = final.append("의 등용에 실패했습니다.");
    }
    showAlert(QString::fromStdString(final));
    clickMapActionBtnWrapUp(false);
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


    setText2(player->get_total_rice());
    setText4(0, 0);
    gameLoop();
}

void MainWindow::gameLoop(){
    clickMapParam=0;
    // 모든 지역에 있는 유닛들 행동력 회복
    vector<State*> all_state = game.get_states();
    for(int i = 0; i < all_state.size(); i++)
        all_state[i]->reset_can_move();

    StateId ai_aggress_state_id = (StateId)0;

    // 현재 플레이어 설정
    current_user = game.get_user_turn();
    setText6(game.get_total_turn(), QString::fromStdString(current_user->get_user_id()));

    QPushButton *controlButtons[] = {ui->btn1,ui->btn2,ui->btn3,ui->btn4,ui->btn5};
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

    // 총 턴과 날짜 표시
    setText5(QString::fromStdString(game.get_date()));
    setText3(100);

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
            showList(show_list, false, 1);
            showAlert(QString::fromStdString(attacked_state->get_state_name()).append("이 공격당했습니다.\n출전시킬 영웅을 고르세요."));
        }
    }

    Player *player = static_cast<Player*>(game.get_users().at(0));

    string input_state;
    string input_hero;
    string command;

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
    ui->line_edit->setAttribute(Qt::WA_MacShowFocusRect,0);

    ui->buttonGrid->hide();
    ui->container2->hide();
    ui->container3->hide();
    ui->container5->hide();
    ui->alertDialog->hide();
    ui->inputDialog->hide();
    ui->selectionDialog->hide();
    ui->listDialog->hide();


    connect(ui->btn_id_confirm, SIGNAL(released()),this, SLOT(setUserID()));
    connect(ui->btn_hero_1, SIGNAL(released()),this, SLOT(setHero1()));
    connect(ui->btn_hero_2, SIGNAL(released()),this, SLOT(setHero2()));
    connect(ui->btn_hero_3, SIGNAL(released()),this, SLOT(setHero3()));
    connect(ui->btn_hero_4, SIGNAL(released()),this, SLOT(setHero4()));


    QSignalMapper* signalMapper = new QSignalMapper (this) ;
//    disconnectMap();
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
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(clickMap(int)));

    connect(ui->btn1, SIGNAL(released()),this, SLOT(clickMapActionBtn1()));
    connect(ui->btn2, SIGNAL(released()),this, SLOT(clickMapActionBtn2()));
    connect(ui->btn3, SIGNAL(released()),this, SLOT(clickMapActionBtn3()));
    connect(ui->btn4, SIGNAL(released()),this, SLOT(clickMapActionBtn4()));
    connect(ui->btn5, SIGNAL(released()),this, SLOT(clickMapActionBtn5()));

    connect(ui->alert_btn, SIGNAL(released()),this, SLOT(closeAlert()));
//    connect(ui->selection_cancel_btn, SIGNAL(released()),this, SLOT(closeSelectionCancel()));
//    connect(ui->selection_accept_btn, SIGNAL(released()),this, SLOT(closeSelectionAccept()));

    connect(ui->input_accept_btn, SIGNAL(released()), this, SLOT(closeInputDialogRecruit()));
    connect(ui->input_accept_war_btn, SIGNAL(released()), this, SLOT(closeInputDialogWar()));

    connect(ui->selection_accept_btn, SIGNAL(released()),this, SLOT(selectionRecruitA()));
    connect(ui->selection_cancel_btn, SIGNAL(released()),this, SLOT(selectionRecruitC()));

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
    showAlert(QString("이성계를 선택했습니다.\n함경도에서 시작합니다!"));
    initial_state = game.get_states().at(0);
    setHero();
}
void MainWindow::setHero2(){
    showAlert(QString("견훤을 선택했습니다.\n전라도에서 시작합니다!"));
    initial_state = game.get_states().at(7);
    setHero();
}
void MainWindow::setHero3(){
    showAlert(QString("문무왕을 선택했습니다.\n경상도에서 시작합니다!"));
    initial_state = game.get_states().at(6);
    setHero();
}
void MainWindow::setHero4(){
    showAlert(QString("고려 광종을 선택했습니다.\n황해도에서 시작합니다!"));
    initial_state = game.get_states().at(3);
    setHero();
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

