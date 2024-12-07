// Cellule.h
#ifndef CELLULE_H
#define CELLULE_H

enum CellState {
    VIDE,      // Cellule vide
    VIVANT,    // Cellule vivante
    OBSTACLE   // Cellule obstacle
    // L'�tat MORT a �t� supprim� car il est redondant avec VIDE
};

#endif // CELLULE_H
