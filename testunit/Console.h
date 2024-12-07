#pragma once
// interfaces/Console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include "SimulationInterface.h"
#include <string>

/**
 * @brief Interface console pour la simulation.
 *
 * Cette classe g�re l'affichage et la mise � jour de la grille dans la console.
 */
class ConsoleInterface : public SimulationInterface {
public:
    /**
     * @brief Ex�cute la simulation en mode console.
     *
     * @param grid R�f�rence vers la grille de simulation.
     * @param delay D�lai entre chaque it�ration en millisecondes.
     * @param maxIterations Nombre maximal d'it�rations (0 pour infini).
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
    // Effacer le fichier de sortie avant de commencer une nouvelle ex�cution
    ofstream outputFile("output.txt", ios::trunc);  // Ouvre le fichier en mode troncature
    if (!outputFile.is_open()) {
        cerr << "Impossible d'ouvrir le fichier de sortie." << endl;
        return;
    }

    // Demander � l'utilisateur de sp�cifier le nombre d'it�rations (s'il n'est pas d�fini)
    if (maxIterations == 0) {
        cout << "Entrez le nombre d'it�rations (0 pour illimit�): ";
        while (!(cin >> maxIterations) || maxIterations < 0) {
            cout << "Veuillez entrer un nombre entier positif valide: ";
            cin.clear();  // Enlever l'�tat d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorer les mauvaises entr�es
        }
    }

    int iterationsCount = 0;
    while (maxIterations == 0 || iterationsCount < maxIterations) {
        grid.print();  // Afficher la grille dans la console
        grid.update();  // Mettre � jour la grille
        iterationsCount++;

        // Sauvegarder l'�tat de la grille apr�s chaque it�ration
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
        outputFile << "-----------------------" << endl; // S�parateur entre les �tats

        // V�rifier si l'automate est stable
        if (grid.hasStableState()) {
            cout << "La grille a atteint un �tat stable. Fin de la simulation." << endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    cout << "Simulation termin�e apr�s " << iterationsCount << " it�rations." << endl;

    // Fermer le fichier apr�s l'�criture
    outputFile.close();
}