#pragma once
//#include "source.hpp"
#include "Header.hpp"
#include <iostream>


class Button : public sf::Drawable
{
public:

/*
default constructor
*/
Button()
{
    box = sf::RectangleShape();
    text = sf::Text();
}
// custom constructor for text and font input
Button(std::string _text, sf::Font& _font)
{

    text = sf::Text(_text, _font, 30);
    text.setFillColor(sf::Color::White);
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);
    this->centerBoxPos();
}

// overwrite the draw function to to draw properly
protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(box, states);
        target.draw(text, states);
    }


private:

void centerBoxPos()
{
    // set start position for box and size based on string size (experimental)
    box.setPosition(sf::Vector2f(500, 500));
    box.setSize(sf::Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 20));

    // set the text inside the box relative to size and position (experimental)
    text.setPosition(
        box.getPosition().x + (box.getSize().x - text.getLocalBounds().width) / 2,
        box.getPosition().y - 10/*experimental offset for y*/ + (box.getSize().y - text.getLocalBounds().height) / 2
        );

}

sf::RectangleShape box;
sf::Text text;

};