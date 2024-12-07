// components/Grid.h
#ifndef GRID_H
#define GRID_H

#include "Cellule.h"
#include <vector>
#include <stack>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @brief Classe représentant la grille de simulation.
 *
 * Cette classe gère l'état de chaque cellule, les mises à jour de la grille,
 * les opérations d'annulation, et le dessin de la grille dans l'interface graphique.
 */
class Grid {
private:
    std::vector<std::vector<CellState>> cells;
    std::stack<std::vector<std::vector<CellState>>> history; // Pile pour stocker les états précédents
    int rows;
    int cols;

    /**
     * @brief Compte le nombre de voisins vivants autour d'une cellule.
     *
     * @param x Position X de la cellule.
     * @param y Position Y de la cellule.
     * @return int Nombre de voisins vivants.
     */
    int countLivingNeighbors(int x, int y);

    /**
     * @brief Sauvegarde l'état actuel de la grille dans l'historique.
     */
    void saveState();

public:
    /**
     * @brief Constructeur de la grille.
     *
     * @param r Nombre de lignes.
     * @param c Nombre de colonnes.
     */
    Grid(int r, int c);

    /**
     * @brief Initialise la grille à partir d'un fichier.
     *
     * @param filename Nom du fichier contenant la configuration initiale.
     */
    void initializeFromInput(const std::string& filename);

    /**
     * @brief Met à jour la grille selon les règles de la simulation.
     */
    void update();

    /**
     * @brief Annule la dernière mise à jour de la grille.
     */
    void undo();

    /**
     * @brief Vérifie si la grille a atteint un état stable.
     *
     * @return true Si la grille est stable.
     * @return false Sinon.
     */
    bool hasStableState() const;

    /**
     * @brief Dessine la grille dans une fenêtre SFML.
     *
     * @param window Référence à la fenêtre SFML.
     * @param cellSize Taille de chaque cellule en pixels.
     */
    void draw(sf::RenderWindow& window, int cellSize) const;

    /**
     * @brief Bascule l'état d'une cellule en fonction des coordonnées de la souris.
     *
     * @param mouseX Position X de la souris.
     * @param mouseY Position Y de la souris.
     * @param cellSize Taille de chaque cellule en pixels.
     * @param state Nouvel état à attribuer à la cellule.
     */
    void toggleCell(int mouseX, int mouseY, int cellSize, CellState state);

    /**
     * @brief Affiche la grille dans la console.
     */
    void print() const;

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    CellState getCellState(int row, int col) const { return cells[row][col]; }
};

#endif // GRID_H