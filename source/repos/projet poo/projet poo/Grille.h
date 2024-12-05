#ifndef GRILLE_H
#define GRILLE_H
#include <string> 
#include <vector>
#include <stack>
#include "Cellule.h"

class Grid {
private:
    std::vector<std::vector<CellState>> cells;
    std::stack<std::vector<std::vector<CellState>>> history;
    int rows;
    int cols;

    int countLivingNeighbors(int x, int y);
    void saveState();

public:
    Grid(int r, int c);
    void initializeFromInput(const std::string& filename);
    void update();
    void undo();
    bool hasStableState() const;
    void toggleCell(int mouseX, int mouseY, int cellSize, CellState state);
    void print() const;
    const std::vector<std::vector<CellState>>& getCells() const;
};

#endif // GRILLE_H
