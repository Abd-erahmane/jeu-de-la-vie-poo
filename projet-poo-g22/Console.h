// interfaces/Console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include "SimulationInterface.h"
#include <string>

/**
 * @brief Interface console pour la simulation.
 *
 * Cette classe gère l'affichage et la mise à jour de la grille dans la console.
 */
class ConsoleInterface : public SimulationInterface {
public:
    /**
     * @brief Exécute la simulation en mode console.
     *
     * @param grid Référence vers la grille de simulation.
     * @param delay Délai entre chaque itération en millisecondes.
     * @param maxIterations Nombre maximal d'itérations (0 pour infini).
     */
    void run(Grid& grid, int delay, int maxIterations) override;
};

#endif // CONSOLE_H
