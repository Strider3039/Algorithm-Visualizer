#pragma once
#include <SFML/Window/Window.hpp>
#include "Header.hpp"
#include <SFML/System/Vector2.hpp>

class Button : public sf::Drawable
{
public:

/*
default constructor
*/
Button() {}
// custom constructor for text and font input
Button(std::string _text, sf::Font& _font, sf::Vector2f position, double width)
{

    text = sf::Text(_text, _font, 30);
    text.setFillColor(sf::Color::White);

    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(5);
    positionVector = position;
    boxWidth = width;

    this->centerBoxPos();
    
}


/*
added bool return value. returns true when button is clicked
*/
// create the scroll and click actions for button
bool scrollAndClick(sf::Event event, sf::Window& window)
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
            return true;
        }
    }

    // reset box colors after scrolling away
    if (!box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(5);
    }

    return false;
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

sf::Vector2f _getPosition()
{
    
}

/*
set color of button/text.
*/
void _setColor(sf::Color color)
{
    box.setOutlineColor(color);
    text.setFillColor(color);
}

std::string _getText()
{
    return text.getString();
}


/*
sets std callback function
*/
void setCallback(std::function<void()> callback)
{
    onClick = callback;
}

void triggerCallback() 
{
    if (onClick) { onClick(); }
}

// overwrite the draw function to to draw properly
protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(box, states);
        target.draw(text, states);
    }

    void centerBoxPos()
    {
        // set start position to middle of screen for box and height based on string height (experimental)
        // position is center of screen - half the box size to truely center
        // NOTE: set constant box width
        box.setSize(sf::Vector2f(boxWidth, text.getLocalBounds().height + 20));
        box.setPosition(positionVector.x - box.getSize().x / 2, positionVector.y - box.getSize().y / 2);

        // set the text inside the box relative to size and position (experimental)
        text.setPosition(
            box.getPosition().x + (box.getSize().x - text.getLocalBounds().width) / 2,
            box.getPosition().y - 10/*experimental offset for y*/ + (box.getSize().y - text.getLocalBounds().height) / 2
            );

    }

private:

std::function<void()> onClick;



sf::RectangleShape box;
sf::Vector2f positionVector;
double boxWidth;
sf::Text text;


};

