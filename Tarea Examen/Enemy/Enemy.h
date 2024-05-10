//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"
#include <vector>
struct Action;
class Player;

class Enemy: public Character {
private:
    int experienceValue;
    vector<Enemy*> enemies;

public:
    int maxHealth;
    Enemy(char*, int, int, int, int, int);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    void mostrarEstado ();
    void incrementarEstadisticas(int cantidad);
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> player);
    int getExperienceValue();

    const std::vector<Enemy*>& getEnemies() const {
        return enemies;
    }

};


#endif //RPG_ENEMY_H
