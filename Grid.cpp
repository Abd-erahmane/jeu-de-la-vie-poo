// components/Grid.cpp
#include "Grid.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, vector<CellState>(cols, VIDE));
}

void Grid::initializeFromInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier.");
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

int Grid::countLivingNeighbors(int x, int y) {
    int livingNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newX = (x + i + rows) % rows;
            int newY = (y + j + cols) % cols;

            if (cells[newX][newY] == VIVANT) {
                livingNeighbors++;
            }
        }
    }
    return livingNeighbors;
}

void Grid::saveState() {
    history.push(cells); // Sauvegarder l'état actuel dans la pile
}

void Grid::update() {
    saveState(); // Sauvegarder l'état avant la mise à jour
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
}

void Grid::undo() {
    if (!history.empty()) {
        cells = history.top(); // Restaurer l'état précédent
        history.pop();         // Retirer cet état de la pile
    }
}

bool Grid::hasStableState() const {
    if (history.empty()) return false;
    return cells == history.top(); // Comparer avec l'état précédent
}

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
