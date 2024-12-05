#ifndef BUTTON_H
#define BUTTON_H
#include <string> 
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button(float x, float y, float width, float height, sf::Font& font, const std::string& label, const sf::Color& color);
    void setColor(const sf::Color& color);
    void draw(sf::RenderWindow& window);
    bool isClicked(float mouseX, float mouseY);
};

#endif // BUTTON_H
