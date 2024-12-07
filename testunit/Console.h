#pragma once
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
// interfaces/Console.cpp
#include "Console.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream> // Ajouter pour la gestion de fichier

using namespace std;

void ConsoleInterface::run(Grid& grid, int delay, int maxIterations) {
    // Effacer le fichier de sortie avant de commencer une nouvelle exécution
    ofstream outputFile("output.txt", ios::trunc);  // Ouvre le fichier en mode troncature
    if (!outputFile.is_open()) {
        cerr << "Impossible d'ouvrir le fichier de sortie." << endl;
        return;
    }

    // Demander à l'utilisateur de spécifier le nombre d'itérations (s'il n'est pas défini)
    if (maxIterations == 0) {
        cout << "Entrez le nombre d'itérations (0 pour illimité): ";
        while (!(cin >> maxIterations) || maxIterations < 0) {
            cout << "Veuillez entrer un nombre entier positif valide: ";
            cin.clear();  // Enlever l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorer les mauvaises entrées
        }
    }

    int iterationsCount = 0;
    while (maxIterations == 0 || iterationsCount < maxIterations) {
        grid.print();  // Afficher la grille dans la console
        grid.update();  // Mettre à jour la grille
        iterationsCount++;

        // Sauvegarder l'état de la grille après chaque itération
        for (int i = 0; i < grid.getRows(); ++i) {
            for (int j = 0; j < grid.getCols(); ++j) {
                if (grid.getCellState(i, j) == VIVANT) {
                    outputFile << "1 ";
                }
                else if (grid.getCellState(i, j) == OBSTACLE) {
                    outputFile << "X ";
                }
                else {
                    outputFile << "0 ";
                }
            }
            outputFile << endl;
        }
        outputFile << "-----------------------" << endl; // Séparateur entre les états

        // Vérifier si l'automate est stable
        if (grid.hasStableState()) {
            cout << "La grille a atteint un état stable. Fin de la simulation." << endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    cout << "Simulation terminée après " << iterationsCount << " itérations." << endl;

    // Fermer le fichier après l'écriture
    outputFile.close();
}