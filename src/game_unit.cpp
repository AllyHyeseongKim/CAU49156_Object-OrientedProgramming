#include "../headers/game_unit.h"

// constructor

GameUnit::GameUnit(std::string name, int strength, int leadership, int wisdom, int political, int attraction, UnitStatus status) {
    this->name = name;
    this->strength = strength;
    this->leadership = leadership;
    this->wisdom = wisdom;
    this->political = political;
    this->attraction = attraction;
    this->status = status;
    
    this->can_move = true;   
}

// getter

std::string GameUnit::get_name() const {
    return name;
}

int GameUnit::get_strength() const {
    return strength;
}

int GameUnit::get_leadearship() const {
    return leadership;
}

int GameUnit::get_wisdom() const {
    return wisdom;
}

int GameUnit::get_political() const {
    return political;
}

int GameUnit::get_attraction() const {
    return attraction;
}

UnitStatus GameUnit::get_status() const {
    return status;
}

bool GameUnit::get_can_move() const {
    return can_move;
}

// setter

void GameUnit::set_strength(int strength) {
    this->strength = strength;
}

void GameUnit::set_leadership(int leadership) {
    this->leadership = leadership;
}

void GameUnit::set_wisdom(int wisdom) {
    this->wisdom = wisdom;
}

void GameUnit::set_political(int political) {
    this->political = political;
}

void GameUnit::set_attraction(int attraction) {
    this->attraction = attraction;
}

void GameUnit::set_status(UnitStatus status) {
    this->status = status;
}

void GameUnit::set_can_move(bool can_move) {
    this->can_move = can_move;
}

bool operator==(GameUnit& unit1, GameUnit& unit2) {
    return (unit1.name == unit2.name) && (unit1.leadership == unit2.leadership) 
    && (unit1.political == unit2.political) && (unit1.strength == unit2.strength) && (unit1.wisdom == unit2.wisdom)
    && (unit1.can_move == unit2.can_move);
}