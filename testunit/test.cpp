// test_Grid.cpp
#include "pch.h" // Inclure les précompilés si nécessaire
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
        // Nettoyage après chaque test
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

    // Vérifier que toutes les cellules sont initialement VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait être VIDE";
        }
    }
}

// Test de l'initialisation à partir d'un fichier
TEST_F(GridTests, TestInitializeFromInput) {
    std::ofstream outFile("Grid.txt");
    // Écriture d'une configuration de 5 lignes et 10 colonnes
    // Exemple de configuration avec quelques cellules VIVANT et OBSTACLE
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 1 0 0 0 0 0 0\n";
    outFile << "0 1 X 1 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    // Initialiser la grille à partir du fichier corrigé
    grid->initializeFromInput("Grid.txt"); // Correction ici

    // Vérifier les cellules spécifiques
    EXPECT_EQ(grid->getCellState(0, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 2), OBSTACLE);
    EXPECT_EQ(grid->getCellState(2, 3), VIVANT);

    // Vérifier que les autres cellules sont VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 0 && j == 2) ||
                (i == 1 && j == 3) ||
                (i == 2 && (j == 1 || j == 2 || j == 3))) {
                continue; // Ces cellules ont déjà été vérifiées
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait être VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de la mise à jour de la grille avec un oscillateur "blinker"
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

    // Effectuer une mise à jour pour passer à l'état horizontal
    grid->update();

    // Vérifier l'état après la mise à jour (blinker horizontal)
    EXPECT_EQ(grid->getCellState(1, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);

    // Vérifier que les anciennes cellules verticales sont désormais VIDE
    EXPECT_EQ(grid->getCellState(0, 2), VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // Vérifier que les autres cellules restent VIDE ou OBSTACLE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 1 && (j == 1 || j == 2 || j == 3))) {
                continue; // Ces cellules ont déjà été vérifiées
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait être VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de l'annulation de la dernière mise à jour
TEST_F(GridTests, TestUndo) {
    // Initialiser la grille avec un état initial
    std::ofstream outFile("Grid.txt");
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 1 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile << "0 0 0 0 0 0 0 0 0 0\n";
    outFile.close();

    grid->initializeFromInput("Grid.txt");

    // Effectuer une mise à jour
    grid->update();

    // Vérifier l'état après la mise à jour
    EXPECT_EQ(grid->getCellState(1, 1), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 3), VIVANT);
    EXPECT_EQ(grid->getCellState(0, 2), VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // Annuler la mise à jour
    grid->undo();

    // Vérifier que l'état est revenu à l'initial
    EXPECT_EQ(grid->getCellState(0, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(1, 2), VIVANT);
    EXPECT_EQ(grid->getCellState(2, 2), VIVANT);

    // Vérifier que les autres cellules sont VIDE
    for (int i = 0; i < grid->getRows(); ++i) {
        for (int j = 0; j < grid->getCols(); ++j) {
            if ((i == 0 && j == 2) ||
                (i == 1 && j == 2) ||
                (i == 2 && j == 2)) {
                continue; // Ces cellules ont déjà été vérifiées
            }
            EXPECT_EQ(grid->getCellState(i, j), VIDE) << "Cellule (" << i << ", " << j << ") devrait être VIDE";
        }
    }

    // Nettoyage
    remove("Grid.txt");
}

// Test de la méthode hasStableState avec une configuration stable
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

    // Avant la mise à jour, la grille ne devrait pas être stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une mise à jour
    grid->update();

    // Après la mise à jour, la grille devrait être stable
    EXPECT_TRUE(grid->hasStableState());

    // Nettoyage
    remove("Grid.txt");
}

// Test de la méthode hasStableState avec un oscillateur
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

    // Avant la mise à jour, la grille ne devrait pas être stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une première mise à jour
    grid->update();

    // Après une mise à jour, la grille ne devrait toujours pas être stable
    EXPECT_FALSE(grid->hasStableState());

    // Effectuer une seconde mise à jour pour revenir à l'état initial
    grid->update();

    // Maintenant, la grille ne devrait pas être stable (car elle oscille entre deux états)
    EXPECT_FALSE(grid->hasStableState());

    // Nettoyage
    remove("Grid.txt");
}

// Test de basculement de l'état d'une cellule
TEST_F(GridTests, TestToggleCell) {
    // Basculer une cellule de VIDE à VIVANT
    grid->toggleCell(2, 2, 1, VIVANT); // Supposons cellSize = 1 pour simplifier
    EXPECT_EQ(grid->getCellState(2, 2), VIVANT);

    // Basculer la même cellule de VIVANT à VIDE
    grid->toggleCell(2, 2, 1, VIDE);
    EXPECT_EQ(grid->getCellState(2, 2), VIDE);

    // Basculer une cellule en OBSTACLE
    grid->toggleCell(1, 1, 1, OBSTACLE);
    EXPECT_EQ(grid->getCellState(1, 1), OBSTACLE);

    // Tenter de basculer une cellule en VIVANT qui est déjà un OBSTACLE
    grid->toggleCell(1, 1, 1, VIVANT);
    EXPECT_EQ(grid->getCellState(1, 1), OBSTACLE) << "Les obstacles ne doivent pas être modifiables par toggleCell sauf pour les OBSTACLE";
}

// Test de la méthode print (capturer la sortie standard)
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

    // Vérifier la sortie capturée
    std::string expectedOutput =
        "1 0 0 0 0 0 0 0 0 0 \n"
        "0 X 0 0 0 0 0 0 0 0 \n"
        "0 0 1 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 0 0 0 \n"
        "0 0 0 0 0 0 0 0 0 0 \n"
        "-----------------------\n";

    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

// Main pour exécuter tous les tests
int main(int argc, char** argv) {
    // Configuration pour afficher les caractères UTF-8 correctement dans la console Windows
#ifdef _WIN32
    // Vous pouvez ajouter des configurations spécifiques à Windows ici si nécessaire
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
