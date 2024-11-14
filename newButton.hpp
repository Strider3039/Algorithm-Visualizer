#pragma once
//#include "source.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


class Button : public sf::Drawable
{
public:

/*
defualt constructor
*/
Button()
{
    box = sf::RectangleShape();
    text = sf::Text();
}
Button(std::string _text, sf::Font _font)
{
    // text.setString(_text);
    // text.setFont(_font);
    // text.setFillColor(sf::Color::Red);

    text = sf::Text(_text, _font, 40);
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(500, 500));

    box.setFillColor(sf::Color::Cyan);
    this->centerBoxPos();
}

protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(box, states);
        target.draw(text, states);
    }


private:

void centerBoxPos()
{
    box.setPosition(sf::Vector2f(text.getPosition().x + 10, text.getPosition().y + 10));
    box.setSize(sf::Vector2f(text.getLocalBounds().width + 10, text.getLocalBounds().height + 10));
}

sf::RectangleShape box;
sf::Text text;

};