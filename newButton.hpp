#pragma once

#include "Header.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

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
Button(std::string _text, sf::Font& _font, sf::Vector2f position)
{

    text = sf::Text(_text, _font, 30);
    text.setFillColor(sf::Color::White);

    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);
    positionVector = position;

    this->centerBoxPos();
    
}

// create the scroll and click actions for button
void scrollAndClick(sf::Event event, sf::Window& window)
{

    // get the postition of the mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // check for intersection of mouse point and box global bounds
    if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        
        box.setOutlineColor(sf::Color::Cyan);
        box.setOutlineThickness(7);

        // check for mouse left click while within box global bounds
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            box.setOutlineColor(sf::Color::Green);
        }
    }

    // reset box colors after scrolling away
    if (!box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(5);
    }


}


/*
return the global bounds of the button
*/
sf::FloatRect _getBounds()
{
    return box.getGlobalBounds();
}

/*
set the position of the button. updates position vector and centers button.
*/
void _setPosititon(sf::Vector2f position)
{
    positionVector = position;
    this->centerBoxPos();
}

/*
set color of button/text.
*/
void _setColor(sf::Color color)
{
    box.setOutlineColor(color);
    text.setFillColor(color);
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
    // set start position to middle of screen for box and height based on string height (experimental)
    // position is center of screen - half the box size to truely center
    // NOTE: set constant box width
    box.setSize(sf::Vector2f(250, text.getLocalBounds().height + 20));
    box.setPosition(positionVector.x - box.getSize().x / 2, positionVector.y - box.getSize().y / 2);

    // set the text inside the box relative to size and position (experimental)
    text.setPosition(
        box.getPosition().x + (box.getSize().x - text.getLocalBounds().width) / 2,
        box.getPosition().y - 10/*experimental offset for y*/ + (box.getSize().y - text.getLocalBounds().height) / 2
        );

}

sf::RectangleShape box;
sf::Text text;
sf::Vector2f positionVector;

};