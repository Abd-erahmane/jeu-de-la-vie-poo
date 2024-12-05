#include "Grille.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string> 
Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<CellState>(cols, VIDE));
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
    history.push(cells);
}

void Grid::initializeFromInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int state;
            file >> state;
            cells[i][j] = static_cast<CellState>(state);
        }
    }
    file.close();
}

void Grid::update() {
    saveState();
    std::vector<std::vector<CellState>> newCells = cells;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j] == OBSTACLE) continue;

            int livingNeighbors = countLivingNeighbors(i, j);
            if (cells[i][j] == VIVANT) {
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[i][j] = VIDE;
                }
            }
            else if (livingNeighbors == 3) {
                newCells[i][j] = VIVANT;
            }
        }
    }
    cells = newCells;
}

void Grid::undo() {
    if (!history.empty()) {
        cells = history.top();
        history.pop();
    }
}

bool Grid::hasStableState() const {
    if (history.empty()) return false;
    return cells == history.top();
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
            std::cout << (cells[i][j] == VIVANT ? "1 " : (cells[i][j] == OBSTACLE ? "X " : "0 "));
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

const std::vector<std::vector<CellState>>& Grid::getCells() const {
    return cells;
}
