// interfaces/Graphics.h
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SimulationInterface.h"
#include "Grid.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Interface graphique pour la simulation utilisant SFML.
 *
 * Cette classe gère l'affichage de la grille, les boutons interactifs,
 * et les interactions utilisateur via une fenêtre graphique.
 */
class GraphicsInterface : public SimulationInterface {
public:
    /**
     * @brief Exécute la simulation en mode graphique.
     *
     * @param grid Référence vers la grille de simulation.
     * @param delay Délai entre chaque itération en millisecondes.
     * @param maxIterations Nombre maximal d'itérations (0 pour infini).
     */
    void run(Grid& grid, int delay, int maxIterations) override;
};

#endif // GRAPHICS_H
