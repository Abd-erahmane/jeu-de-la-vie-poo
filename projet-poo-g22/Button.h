// interfaces/Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Classe représentant un bouton interactif.
 *
 * Cette classe gère l'affichage, le changement de couleur, et la détection des clics sur un bouton.
 */
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    /**
     * @brief Constructeur du bouton.
     *
     * @param x Position X du bouton.
     * @param y Position Y du bouton.
     * @param width Largeur du bouton.
     * @param height Hauteur du bouton.
     * @param font Référence à la police utilisée pour le texte.
     * @param label Texte affiché sur le bouton.
     * @param color Couleur de remplissage du bouton.
     */
    Button(float x, float y, float width, float height, sf::Font& font, const std::string& label, const sf::Color& color);

    /**
     * @brief Change la couleur du bouton.
     *
     * @param color Nouvelle couleur de remplissage.
     */
    void setColor(const sf::Color& color);

    /**
     * @brief Dessine le bouton dans la fenêtre.
     *
     * @param window Référence à la fenêtre SFML.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Vérifie si le bouton a été cliqué.
     *
     * @param mouseX Position X de la souris.
     * @param mouseY Position Y de la souris.
     * @return true Si le bouton a été cliqué.
     * @return false Sinon.
     */
    bool isClicked(float mouseX, float mouseY);
};

#endif // BUTTON_H
