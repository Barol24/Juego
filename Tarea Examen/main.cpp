#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>
#include <vector>
using namespace std;

int main() {
    Player *player = new Player("Simi", 35, 7, 2, 10, 100, "Mexicana");
    Enemy *enemy = new Enemy("Mamalucha", 30, 5, 2, 7, 50);
    Enemy *enemy2 = new Enemy("Duolingo", 30, 4, 2, 2, 50);

    cout << "=== RPG Battle ===" << endl;

    cout << "=================" << endl;

    vector<Character*> participants = {player, enemy, enemy2};
    Combat* combat = new Combat(participants);

    // Ejecución del combate
    combat->doCombat();

    // Otorgar experiencia al jugador y aumentar estadísticas de enemigos
    combat->grantExperience();
    combat->increaseEnemyStats();






    // std::cout << "\nEstado inicial del enemigo:" << std::endl;
    // enemy->mostrarEstado();
    // std::cout << std::endl;

    // Derrotar enemigos
    //Player.gainExperience(int expe);
    // std::cout << "\nDespués de derrotar un enemigo:" << std::endl;
    //  Player.mostrarEstado();

    // Subir de nivel
    // Player->derrotarEnemigo(60);
    // std::cout << "\nDespués de subir de nivel:" << std::endl;
    // Player->mostrarEstado();

    // Incrementar estadísticas del enemigo
    // enemy->incrementarEstadisticas(5);
    //  std::cout << "\nEstado del enemigo después de incrementar sus estadísticas:" << std::endl;
    //  enemy->mostrarEstado();




    // vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    //Combat* combat = new Combat(participants);
    // combat->doCombat();
    char* buffer = player -> serialize();

    Player* otroPlayer = Player::unserialize(buffer);

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
