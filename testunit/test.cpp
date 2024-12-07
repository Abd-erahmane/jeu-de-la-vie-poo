// test_Grid.cpp
#include "pch.h" // Inclure les pr�compil�s si n�cessaire
#include "Grid.h"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <vector>

// Classe de test pour Grid utilisant Google Test
class GridTests : public ::testing::Test {

protected:
    void SetUp() override {
        // Initialisation avant chaque test
        rows = 5;
        cols = 10;
        grid = new Grid(rows, cols);
    }

    void TearDown() override {
        // Nettoyage apr�s chaque test
        delete grid;
    }

    Grid* grid;
    int rows;
    int cols;
};

// Test du constructeur
TEST_F(GridTests, TestConstructor) {
    EXPECT_EQ(grid->getRows(), 5);
    EXPECT_EQ(grid->getCols(), 10);

    // V�rifier que toutes les cellules sont initialement VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait �tre VIDE";
        }
    }
}

// Test de l'initialisation � partir d'un fichier
TEST_F(GridTests, TestInitializeFromInput) {
    std::ofstream outFile("Grid.txt");
    // �criture d'une configuration de 5 lignes et 10 colonnes
    // Exemple de configuration avec quelques cellules VIVANT et OBSTACLE
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 1 0 0 0 0 0 0\n";
    outFile << "0 1 X 1 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    // Initialiser la grille � partir du fichier corrig�
    grid->initializeFromInput("Grid.txt"); // Correction ici

    // V�rifier les cellules sp�cifiques
    EXPECT_EQ(grid->getCellState(0, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 2), OBSTACLE);
    EXPECT_EQ(grid->getCellState(2, 3), VIVANT);

    // V�rifier que les autres cellules sont VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 0 && j == 2) ||
                (i == 1 && j == 3) ||
                (i == 2 && (j == 1 || j == 2 || j == 3))) {
                continue; // Ces cellules ont d�j� �t� v�rifi�es
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait �tre VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de la mise � jour de la grille avec un oscillateur "blinker"
TEST_F(GridTests, TestUpdate) {
    // Initialiser la grille avec un oscillateur "blinker" vertical
    std::ofstream outFile("Grid.txt");
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    grid->initializeFromInput("Grid.txt"); // Utiliser le bon nom de fichier

    // Effectuer une mise � jour pour passer � l'�tat horizontal
    grid->update();

    // V�rifier l'�tat apr�s la mise � jour (blinker horizontal)
    EXPECT_EQ(grid->getCellState(1, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);

    // V�rifier que les anciennes cellules verticales sont d�sormais VIDE
    EXPECT_EQ(grid->getCellState(0, 2), VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // V�rifier que les autres cellules restent VIDE ou OBSTACLE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 1 && (j == 1 || j == 2 || j == 3))) {
                continue; // Ces cellules ont d�j� �t� v�rifi�es
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait �tre VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de l'annulation de la derni�re mise � jour
TEST_F(GridTests, TestUndo) {
    // Initialiser la grille avec un �tat initial
    std::ofstream outFile("Grid.txt");
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    grid->initializeFromInput("Grid.txt");

    // Effectuer une mise � jour
    grid->update();

    // V�rifier l'�tat apr�s la mise � jour
    EXPECT_EQ(grid->getCellState(1, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);
    EXPECT_EQ(grid->getCellState(0, 2), VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // Annuler la mise � jour
    grid->undo();

    // V�rifier que l'�tat est revenu � l'initial
    EXPECT_EQ(grid->getCellState(0, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 2), VIVANT);

    // V�rifier que les autres cellules sont VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 0 && j == 2) ||
                (i == 1 && j == 2) ||
                (i == 2 && j == 2)) {
                continue; // Ces cellules ont d�j� �t� v�rifi�es
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait �tre VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de la m�thode hasStableState avec une configuration stable
TEST_F(GridTests, TestHasStableStateWithStableConfiguration) {
    // Initialiser la grille avec un bloc stable
    std::ofstream outFile("Grid.txt");
    // Bloc de 2x2 cellules vivantes
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 1 1 0 0 0 0 0 0 0\n";
    outFile << "0 1 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    grid->initializeFromInput("Grid.txt");

    // Avant la mise � jour, la grille ne devrait pas �tre stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une mise � jour
    grid->update();

    // Apr�s la mise � jour, la grille devrait �tre stable
    EXPECT_TRUE(grid->hasStableState());

    // Nettoyage
    remove("Grid.txt");
}

// Test de la m�thode hasStableState avec un oscillateur
TEST_F(GridTests, TestHasStableStateWithOscillator) {
    // Initialiser la grille avec un oscillateur "blinker" vertical
    std::ofstream outFile("Grid.txt");
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    grid->initializeFromInput("Grid.txt");

    // Avant la mise � jour, la grille ne devrait pas �tre stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une premi�re mise � jour
    grid->update();

    // Apr�s une mise � jour, la grille ne devrait toujours pas �tre stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une seconde mise � jour pour revenir � l'�tat initial
    grid->update();

    // Maintenant, la grille ne devrait pas �tre stable (car elle oscille entre deux �tats)
    EXPECT_FALSE(grid->hasStableState());

    // Nettoyage
    remove("Grid.txt");
}

// Test de basculement de l'�tat d'une cellule
TEST_F(GridTests, TestToggleCell) {
    // Basculer une cellule de VIDE � VIVANT
    grid->toggleCell(2, 2, 1, VIVANT); // Supposons cellSize = 1 pour simplifier
    EXPECT_EQ(grid->getCellState(2, 2), VIVANT);

    // Basculer la m�me cellule de VIVANT � VIDE
    grid->toggleCell(2, 2, 1, VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // Basculer une cellule en OBSTACLE
    grid->toggleCell(1, 1, 1, OBSTACLE);
    EXPECT_EQ(grid->getCellState(1, 1), OBSTACLE);

    // Tenter de basculer une cellule en VIVANT qui est d�j� un OBSTACLE
    grid->toggleCell(1, 1, 1, VIVANT);
    EXPECT_EQ(grid->getCellState(1, 1), OBSTACLE) << "Les obstacles ne doivent pas �tre modifiables par toggleCell sauf pour les OBSTACLE";
}

// Test de la m�thode print (capturer la sortie standard)
TEST_F(GridTests, TestPrint) {
    // Rediriger la sortie standard
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::ostringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Initialiser la grille avec quelques cellules
    grid->toggleCell(0, 0, 1, VIVANT);
    grid->toggleCell(1, 1, 1, OBSTACLE);
    grid->toggleCell(2, 2, 1, VIVANT);

    // Appeler print
    grid->print();

    // Restaurer la sortie standard
    std::cout.rdbuf(originalCoutBuffer);

    // V�rifier la sortie captur�e
    std::string expectedOutput =
        "1 0 0 0 0 0 0 0 0 0 \n"
        "0 X 0 0 0 0 0 0 0 0 \n"
        "0 0 1 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 0 0 0 \n"
        "-----------------------\n";

    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

// Main pour ex�cuter tous les tests
int main(int argc, char** argv) {
    // Configuration pour afficher les caract�res UTF-8 correctement dans la console Windows
#ifdef _WIN32
    // Vous pouvez ajouter des configurations sp�cifiques � Windows ici si n�cessaire
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
