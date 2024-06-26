//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(char* name, int health, int attack, int defense, int speed, int expValue) : Character(name, health, attack, defense, speed, false), experienceValue(expValue) {

    maxHealth = health;
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<getName()<<" has died"<<endl;
    }
    else {
        cout<<getName()<<" has taken " << damage << " damage" << endl;
    }
}

void Enemy :: mostrarEstado () {

    cout << "Ataque: " << attack << endl;
    cout << "Defensa: " << defense << endl;
    cout << "Velocidad: " << speed << endl;
}

void Enemy::incrementarEstadisticas(int cantidad) {
    attack += cantidad;
    defense += cantidad;
    speed += cantidad;
}



Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    srand(time(NULL));
    if (this->getHealth() < maxHealth && rand() % 100 < 100){
        myAction.action = [this, target]() {
            this->fleed = true;
        };
    } else {
        myAction.target = target;
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }
    return myAction;
}

