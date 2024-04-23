//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"

struct Action;
class Enemy;

class Player: public Character {
protected:
    int experience;
    int level;
public:
    string nacionalidad = "";
    int poderMagico = 0;
    void mostrar();
    Player(char _name[40], int _health, int _attack, int _defense, int _speed, int poder_, string nacio_);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    Character* getTarget(vector<Enemy*> enemies);

    void flee(vector<Enemy*> enemies);
    void emote();
    void levelUp();
    void gainExperience(int);

    //Podemos hacer que este vector sea polimorfico?
    Action takeAction(vector<Enemy*> enemies);

};


#endif //RPG_PLAYER_H
