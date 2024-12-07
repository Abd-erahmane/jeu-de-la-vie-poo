#pragma once
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
// interfaces/Graphics.cpp

#include <iostream>
#include <thread>
#include <chrono>

void GraphicsInterface::run(Grid& grid, int delay, int maxIterations) {
    int rows = grid.getRows();
    int cols = grid.getCols();
    int cellSize = 19; // Taille des cellules (doit correspondre à celle utilisée dans Grid)

    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize + 100), "Jeu de la Vie");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    Button startButton(10, rows * cellSize + 10, 150, 40, font, "Démarrer", sf::Color::Green);
    Button stopButton(170, rows * cellSize + 10, 150, 40, font, "Arrêter", sf::Color::Red);
    Button undoButton(330, rows * cellSize + 10, 150, 40, font, "Annuler", sf::Color::Blue);

    bool simulationRunning = false;
    CellState currentState = VIVANT; // Commencer avec l'état 'VIVANT'
    int iterationsCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                        simulationRunning = true;   // Démarrer la simulation
                        startButton.setColor(sf::Color::Red);
                        stopButton.setColor(sf::Color::Green);
                    }
                    if (stopButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                        simulationRunning = false;  // Arrêter la simulation
                        startButton.setColor(sf::Color::Green);
                        stopButton.setColor(sf::Color::Red);
                    }
                    if (undoButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                        simulationRunning = false;  // Arrêter la simulation
                        startButton.setColor(sf::Color::Green);  // Réinitialiser l'état des boutons
                        stopButton.setColor(sf::Color::Red);
                        grid.undo();  // Restaurer l'état précédent de la grille
                    }
                    grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize, currentState); // Basculer l'état de la cellule
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize, OBSTACLE); // Ajouter un obstacle
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::V) {
                    currentState = VIVANT;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    currentState = VIDE;
                }
                else if (event.key.code == sf::Keyboard::O) {
                    currentState = OBSTACLE;
                }
            }
        }

        if (simulationRunning) {
            grid.update();
            iterationsCount++;

            // Vérification si la simulation doit être arrêtée
            if (maxIterations > 0 && iterationsCount >= maxIterations) {
                // Arrêter la simulation après le nombre d'itérations maximum
                simulationRunning = false;
                startButton.setColor(sf::Color::Green);
                stopButton.setColor(sf::Color::Red);
            }
            else if (grid.hasStableState()) {
                // Arrêter la simulation si la grille est stable
                simulationRunning = false;
                startButton.setColor(sf::Color::Green);
                stopButton.setColor(sf::Color::Red);
                std::cout << "La grille a atteint un état stable. Fin de la simulation." << std::endl;
            }
        }

        window.clear();
        grid.draw(window, cellSize);
        startButton.draw(window);
        stopButton.draw(window);
        undoButton.draw(window);

        // Affichage du nombre d'itérations effectuées
        sf::Text iterationsText;
        iterationsText.setFont(font);
        iterationsText.setCharacterSize(18);
        iterationsText.setFillColor(sf::Color::Black);
        iterationsText.setPosition(10, rows * cellSize + 50);
        iterationsText.setString("Iterations: " + std::to_string(iterationsCount));
        window.draw(iterationsText);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}