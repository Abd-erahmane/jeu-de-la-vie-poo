#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Grille.h"
#include "Button.h"

using namespace std;

int main() {
    int rows = 25;
    int cols = 25;
    int cellSize = 19;
    int maxIterations = 0;
    int iterationsCount = 0;
    int delay = 500; // Temps d'attente en millisecondes
    string mode;
    string filename;

    cout << "Choisissez le mode (console insérez C et pour le mode graphique insérez G) : ";
    cin >> mode;

    if (mode != "C" && mode != "G") {
        cout << "Mode invalide, veuillez redémarrer et choisir 'C' ou 'G'." << endl;
        return 1;
    }

    cout << "Entrez le délai entre chaque itération en millisecondes (par défaut 500 ms) : ";
    cin >> delay;

    Grid grid(rows, cols);

    if (mode == "G") {
        cout << "Entrez le nombre d'itérations (0 pour une simulation infinie) : ";
        cin >> maxIterations;

        sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize + 100), "Jeu de la Vie");

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Erreur lors du chargement de la police." << endl;
            return -1;
        }

        Button startButton(10, rows * cellSize + 10, 150, 40, font, "Démarrer", sf::Color::Green);
        Button stopButton(170, rows * cellSize + 10, 150, 40, font, "Arrêter", sf::Color::Red);
        Button undoButton(330, rows * cellSize + 10, 150, 40, font, "Annuler", sf::Color::Blue);

        bool simulationRunning = false;
        CellState currentState = VIVANT;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (startButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                            simulationRunning = true;
                            startButton.setColor(sf::Color::Red);
                            stopButton.setColor(sf::Color::Green);
                        }
                        if (stopButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                            simulationRunning = false;
                            startButton.setColor(sf::Color::Green);
                            stopButton.setColor(sf::Color::Red);
                        }
                        if (undoButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                            simulationRunning = false;
                            startButton.setColor(sf::Color::Green);
                            stopButton.setColor(sf::Color::Red);
                            grid.undo();
                        }
                        grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize, currentState);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize, OBSTACLE);
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::V) {
                        currentState = VIVANT;
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        currentState = VIDE;
                    }
                    else if (event.key.code == sf::Keyboard::O) {
                        currentState = OBSTACLE;
                    }
                }
            }

            if (simulationRunning) {
                grid.update();
                iterationsCount++;

                if (maxIterations > 0 && iterationsCount >= maxIterations) {
                    simulationRunning = false;
                    startButton.setColor(sf::Color::Green);
                    stopButton.setColor(sf::Color::Red);
                }
                else if (grid.hasStableState()) {
                    simulationRunning = false;
                    startButton.setColor(sf::Color::Green);
                    stopButton.setColor(sf::Color::Red);
                }
            }

            window.clear();
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                    cell.setPosition(j * cellSize, i * cellSize);
                    if (grid.getCells()[i][j] == VIVANT) {
                        cell.setFillColor(sf::Color::White);
                    }
                    else if (grid.getCells()[i][j] == OBSTACLE) {
                        cell.setFillColor(sf::Color::Red);
                    }
                    else {
                        cell.setFillColor(sf::Color::Black);
                    }
                    window.draw(cell);
                }
            }

            startButton.draw(window);
            stopButton.draw(window);
            undoButton.draw(window);

            sf::Text iterationsText;
            iterationsText.setFont(font);
            iterationsText.setCharacterSize(18);
            iterationsText.setFillColor(sf::Color::Black);
            iterationsText.setPosition(10, rows * cellSize + 50);
            iterationsText.setString("Iterations: " + to_string(iterationsCount));
            window.draw(iterationsText);

            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
    else if (mode == "C") {
        cout << "Entrez le nom du fichier pour initialiser la grille (ou appuyez sur Entrée pour créer une grille vide) : ";
        cin.ignore();
        getline(cin, filename);

        try {
            if (!filename.empty()) {
                grid.initializeFromInput(filename);
            }
        }
        catch (const runtime_error& e) {
            cout << "Erreur : " << e.what() << endl;
            return 1;
        }

        while (true) {
            grid.print();
            grid.update();

            if (grid.hasStableState()) {
                cout << "La grille a atteint un état stable. Fin de la simulation." << endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    return 0;
}
