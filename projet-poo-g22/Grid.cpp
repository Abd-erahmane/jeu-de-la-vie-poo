//Grid.cpp
#include "Grid.h"
#include <iostream>
// components/Grid.cpp

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

// Constructeur de la grille
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, vector<CellState>(cols, VIDE));
    // Vider la pile d'historique lors de la construction
    while (!history.empty()) {
        history.pop();
    }
}

// Initialise la grille � partir d'un fichier
void Grid::initializeFromInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier.");
    }

    // Vider la pile d'historique avant d'initialiser
    while (!history.empty()) {
        history.pop();
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            string token;
            file >> token;
            if (token == "1") {
                cells[i][j] = VIVANT;
            }
            else if (token == "X" || token == "x") {
                cells[i][j] = OBSTACLE;
            }
            else {
                cells[i][j] = VIDE;
            }
        }
    }
    file.close();
}

// Compte le nombre de voisins vivants autour d'une cellule
int Grid::countLivingNeighbors(int x, int y) {
    int livingNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            // V�rifier les limites sans wrapping
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                if (cells[newX][newY] == VIVANT) {
                    livingNeighbors++;
                }
            }
        }
    }
    return livingNeighbors;
}

// Sauvegarde l'�tat actuel de la grille dans l'historique
void Grid::saveState() {
    history.push(cells); // Sauvegarder l'�tat actuel dans la pile
    cout << "Sauvegarde de l'�tat actuel dans l'historique." << endl;
}

// Met � jour la grille selon les r�gles de la simulation
void Grid::update() {
    saveState(); // Sauvegarder l'�tat avant la mise � jour
    vector<vector<CellState>> newCells = cells;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j] == OBSTACLE) continue;

            int livingNeighbors = countLivingNeighbors(i, j);
            if (cells[i][j] == VIVANT) {
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[i][j] = VIDE;
                }
            }
            else {
                if (livingNeighbors == 3) {
                    newCells[i][j] = VIVANT;
                }
            }
        }
    }
    cells = newCells;
    cout << "Mise � jour de la grille termin�e." << endl;
}

// Annule la derni�re mise � jour de la grille
void Grid::undo() {
    if (!history.empty()) {
        cells = history.top(); // Restaurer l'�tat pr�c�dent
        history.pop();         // Retirer cet �tat de la pile
        cout << "Annulation de la derni�re mise � jour." << endl;
    }
    else {
        cout << "Aucun �tat � annuler." << endl;
    }
}

// V�rifie si la grille a atteint un �tat stable
bool Grid::hasStableState() const {
    if (history.empty()) return false;
    return cells == history.top(); // Comparer avec l'�tat pr�c�dent
}

// Dessine la grille dans une fen�tre SFML
void Grid::draw(sf::RenderWindow& window, int cellSize) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);

            if (cells[i][j] == VIVANT) {
                cell.setFillColor(sf::Color::White);
            }
            else if (cells[i][j] == OBSTACLE) {
                cell.setFillColor(sf::Color::Red);
            }
            else {
                cell.setFillColor(sf::Color::Black);
            }

            window.draw(cell);
        }
    }
}

// Bascule l'�tat d'une cellule en fonction des coordonn�es de la souris
void Grid::toggleCell(int mouseX, int mouseY, int cellSize, CellState state) {
    int col = mouseX / cellSize;
    int row = mouseY / cellSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        if (state == OBSTACLE) {
            cells[row][col] = OBSTACLE;
        }
        else if (cells[row][col] != OBSTACLE) {
            cells[row][col] = state;
        }
    }
}

// Affiche la grille dans la console
void Grid::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j] == VIVANT)
                cout << "1 ";
            else if (cells[i][j] == OBSTACLE)
                cout << "X ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;
}