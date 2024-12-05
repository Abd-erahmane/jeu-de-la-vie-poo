#include "Button.h"#include <string> 
Button::Button(float x, float y, float width, float height, sf::Font& font, const std::string& label, const sf::Color& color) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setPosition(x, y);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(static_cast<int>(height * 0.6));
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

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
