// services/Game.h
#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "SimulationInterface.h"
#include <memory> // Pour std::unique_ptr

/**
 * @brief Classe principale contrôlant le flux de l'application.
 *
 * Cette classe gère la sélection du mode d'interface (console ou graphique),
 * l'initialisation de la grille, et l'exécution de la simulation via
 * l'interface sélectionnée.
 */
class Game {
public:
    /**
     * @brief Exécute le jeu.
     */
    void run();
};

#endif // GAME_H
