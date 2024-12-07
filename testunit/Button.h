#pragma once
// interfaces/Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Classe repr�sentant un bouton interactif.
 *
 * Cette classe g�re l'affichage, le changement de couleur, et la d�tection des clics sur un bouton.
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
     * @param font R�f�rence � la police utilis�e pour le texte.
     * @param label Texte affich� sur le bouton.
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
     * @brief Dessine le bouton dans la fen�tre.
     *
     * @param window R�f�rence � la fen�tre SFML.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief V�rifie si le bouton a �t� cliqu�.
     *
     * @param mouseX Position X de la souris.
     * @param mouseY Position Y de la souris.
     * @return true Si le bouton a �t� cliqu�.
     * @return false Sinon.
     */
    bool isClicked(float mouseX, float mouseY);
};

#endif // BUTTON_H
#pragma once
#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font& font, const std::string& label, const sf::Color& color) {
    // Configuration du rectangle
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setPosition(x, y);

    // Configuration du texte
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(static_cast<int>(height * 0.6)); // Taille relative � la hauteur du bouton
    text.setFillColor(sf::Color::Black); // Couleur du texte
    text.setStyle(sf::Text::Bold); // Texte en gras

    // Centrer le texte dans le rectangle
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(x + width / 2, y + height / 2);
}

void Button::setColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(float mouseX, float mouseY) {
    return shape.getGlobalBounds().contains(mouseX, mouseY);
}