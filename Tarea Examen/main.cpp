#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("Simi", 35, 7, 2, 10, 100, "Mexicana");
    Enemy *enemy = new Enemy("Mamalucha", 20, 5, 2, 7);
    Enemy *enemy2 = new Enemy("Duolingo", 30, 4, 2, 2);

    cout << "=== RPG Battle ===" << endl;

    cout << "=================" << endl;

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
