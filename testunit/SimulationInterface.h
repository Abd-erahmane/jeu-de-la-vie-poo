#pragma once
// interfaces/SimulationInterface.h
#ifndef SIMULATIONINTERFACE_H
#define SIMULATIONINTERFACE_H

#include "Grid.h"

/**
 * @brief Classe de base abstraite pour les interfaces de simulation.
 *
 * Cette classe définit une interface commune pour différentes implémentations
 * de l'interface utilisateur de la simulation (console, graphique, etc.).
 */
class SimulationInterface {
public:
    virtual ~SimulationInterface() = default;

    /**
     * @brief Exécute la simulation.
     *
     * @param grid Référence vers la grille de simulation.
     * @param delay Délai entre chaque itération en millisecondes.
     * @param maxIterations Nombre maximal d'itérations (0 pour infini).
     */
    virtual void run(Grid& grid, int delay, int maxIterations) = 0;
};

#endif // SIMULATIONINTERFACE_H