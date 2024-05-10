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
    char* nacionalidad  = "";
    int poderMagico = 0;
    int experiencia = 0;

    void mostrar();
    Player(char* _name , int _health, int _attack, int _defense, int _speed, int poder_, char* nacio_);
    Player(char* _name , int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _experience, int _level);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    char* serialize ();
    static const unsigned int BUFFER_SIZE  = sizeof (name) + sizeof (health) + sizeof (attack) + sizeof (defense) + sizeof (speed) + sizeof (isPlayer) + sizeof (experience) + sizeof (level);

    static Player* unserialize (char* buffer);

    Character* getTarget(vector<Enemy*> enemies);
    void derrotarEnemy(int expGanada);
    void flee(vector<Enemy*> enemies);
    void emote();
    void levelUp();
    void gainExperience(int expe);
    void mostrarEstadisticas ();


    //Podemos hacer que este vector sea polimorfico?
    Action takeAction(vector<Enemy*> enemies);

private:
    char buffer[Player::BUFFER_SIZE];

};


#endif //RPG_PLAYER_H
