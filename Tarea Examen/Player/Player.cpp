//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

void Player::mostrar() {
    cout << "El personaje " << this->getName() << " de nacionalidad " << this->nacionalidad << " esta listo para pelear" << endl;
    cout << "Vida: " << this->getHealth() << "\nPoder Especial: " << this->poderMagico << "\nVelocidad: " << this->getSpeed() << endl;
}



Player::Player(char* name, int health, int attack, int defense, int speed, int _poderMagico, char*   nacio) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    poderMagico = _poderMagico;
    nacionalidad = nacio;
    experience = 25;
    level = 2;
}
Player::Player(char* _name , int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _experience, int _level):Character(_name, _health, _attack, _defense,
        _speed, _isPlayer) {

        experience = _experience;
        level = _level;

}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "You have taken " << damage << " damage" << endl;
    if (health <= 0) {
        cout << "You have died" << endl;
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }

    this->fleed = fleed;
}

void Player::emote() {
    cout << "Jokes on you" << endl;
}

void Player ::derrotarEnemy(int expGanada){
    experiencia += expGanada;
    while (experiencia <= 100) {
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    level++;
    if (experiencia > 100) {
        int remanenteExperiencia = experiencia - 100;
        experiencia = remanenteExperiencia;
    }
    else {
        experiencia = 0;
    }

    attack += 5;
    defense += 2;
    speed += 2;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);

    cout << "¡Has subido al nivel " << level << "!" << endl;
    cout << "Tus características han aumentado: " << endl;
    cout << "Ataque +" << 5 << endl;
    cout << "Defensa +" << 3 << endl;
    cout << "Velocidad +" << 2 << endl;

    for (auto& enemy : enemies) {
        enemy->incrementarEstadisticas(5);
    }

}

void Player::gainExperience(int exp) {
    experience += exp;
    derrotarEnemy(exp);

    }


void Player::mostrarEstadisticas() {
    cout<<"level: " <<level <<::endl;
    cout<<"Experience: "<< experience << ::endl;
    cout<< "attack: " << attack <<:: endl;
    cout << "Defense" << defense << ::endl;

}


Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    cout<<"-----------------------------" << endl;
    mostrar();
    cout << "Choose an action" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Flee"  << endl;
    cin >> option;
    cout<<"-----------------------------" << endl;
    Character *target = nullptr;

    //Esta variable guarda
    //1. Que voy a hacer?
    //2. Con que velocidad/prioridad?
    Action myAction;
    //2.
    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    return myAction;
}
char* Player ::serialize() {
    char* iterador = buffer;
    memcpy(iterador, name, sizeof name);
    iterador += sizeof name;

    memcpy(iterador, &health, sizeof health);
    iterador += sizeof health;

    memcpy(iterador, &attack, sizeof attack);
    iterador += sizeof attack;

    memcpy(iterador, &defense, sizeof defense);
    iterador += sizeof defense;

    memcpy(iterador, &speed, sizeof speed);
    iterador += sizeof speed;

    memcpy(iterador, &isPlayer, sizeof isPlayer);
    iterador += sizeof isPlayer;

    memcpy(iterador, &experience, sizeof experience);
    iterador += sizeof experience;

    memcpy(iterador, &level, sizeof level);
    iterador += sizeof level;
}

Player* Player::unserialize(char* _buffer) {
    char* iterador = _buffer;
    char _name[30];
    int _health;
    int _attack;
    int _defense;
    int _speed;
    bool _isPlayer;
    int _experience;
    int _level;


    memcpy(&_name,iterador,  sizeof _name);
    iterador += sizeof _name;

    memcpy(&_health,iterador,  sizeof _health);
    iterador += sizeof _health;

    memcpy(&_attack,iterador,  sizeof _attack);
    iterador += sizeof _attack;

    memcpy(&_defense,iterador,  sizeof _defense);
    iterador += sizeof _defense;

    memcpy(&_speed,iterador,  sizeof _speed);
    iterador += sizeof _speed;

    memcpy(&_isPlayer,iterador,  sizeof _isPlayer);
    iterador += sizeof _isPlayer;

    memcpy(&_experience,iterador,  sizeof _experience);
    iterador += sizeof _experience;

    memcpy(&_level,iterador,  sizeof _level);


    return new Player(_name, _health, _attack, _defense, _speed, _isPlayer, _experience, _level);

}