#pragma once
#include "Header.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

class TextBox : public sf::Drawable
{
public:

TextBox() {}
/*
modified constructor from Button
*/
TextBox(std::string _text, sf::Font& _font, sf::Vector2f position)
{
    grayColor.r = 100; grayColor.g = 100; grayColor.b = 100;

    outputStr = sf::Text(_text, _font, 30);
    outputStr.setFillColor(grayColor);

    box.setFillColor(sf::Color::White);
    box.setOutlineColor(grayColor);
    box.setOutlineThickness(1);
    positionVector = position;

    this->centerBoxPos();
    
}

/*
updates text member with user input
*/
void write(unsigned int unicode, sf::Window& window)
{
    positionEnteredText();
    _setColor(sf::Color::Black);
    if (unicode == 8) /*backspace functionality*/
    {
        if (inputStr.getSize() != 0) /*error checking for empty string*/
        {
            inputStr.erase(inputStr.getSize() - 1);
        }
        logStr = inputStr;
        cout << logStr << endl;
        outputStr.setString(inputStr);
    }
    else if (unicode == 27) /*problems with escape key*/
    {
        return;
    }
    else if (inputStr.getSize() != 6) /*limit character count to 6*/
    {               
        inputStr += unicode;
        logStr = inputStr;
        cout << logStr << endl;
        outputStr.setString(inputStr);
    }
    if (inputStr.getSize() == 0) /*empty string defaults back to "Insert" gray color*/
    {
        outputStr.setString("type here");
        outputStr.setFillColor(grayColor);
        this->centerBoxPos();
    }
            
}

/*
returns true if cursor intersects box
*/
bool cursorIntersect(sf::Window& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

/*
returns true during left click event within box bounds
*/
bool interaction(sf::Event event, sf::Window& window)
{
    return (cursorIntersect(window) && (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left));
}

/*
modified code from Button 
*/
bool scrollAndClick(sf::Event event, sf::Window& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    /*
    cursor intersects box bounds
    */
    if (this->cursorIntersect(window))
    {
        box.setOutlineThickness(2);

        /*
        left mouse click event on box
        */
        if (this->interaction(event, window))
        {
            box.setOutlineColor(sf::Color::Black);

            return true;
        }
    }
    if (!this->cursorIntersect(window))
    {
        box.setOutlineColor(grayColor);
        box.setOutlineThickness(1);
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

/*
set color of button/text.
*/
void _setColor(sf::Color color)
{
    box.setOutlineColor(color);
    outputStr.setFillColor(color);
}

std::string _getText()
{
    return outputStr.getString();
}

/*
clears box of any input 
*/
void clear()
{
    inputStr.clear();
    outputStr.setString(inputStr);
}

sf::Vector2f getPosition()
{
    return positionVector;
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

protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(box, states);
        target.draw(outputStr, states);
    }

private:

    /*
    reposition text in box to the left. done for visual purposes
    */
    void positionEnteredText()
    {
        outputStr.setPosition(
        box.getPosition().x + (box.getSize().x - outputStr.getLocalBounds().width) / 2.5,
        box.getPosition().y //- 10/*experimental offset for y*/ + (box.getSize().y - outputStr.getLocalBounds().height) / 2
        );
    }

/*
code taken from Button class
*/
    void centerBoxPos()
    {
        // set start position to middle of screen for box and height based on string height (experimental)
        // position is center of screen - half the box size to truely center
        // NOTE: set constant box width
        box.setSize(sf::Vector2f(150, outputStr.getLocalBounds().height + 20));
        box.setPosition(positionVector.x - box.getSize().x / 2, positionVector.y - box.getSize().y / 2);

        // set the text inside the box relative to size and position (experimental)
        outputStr.setPosition(
            box.getPosition().x + (box.getSize().x - outputStr.getLocalBounds().width) / 2,
            box.getPosition().y - 10/*experimental offset for y*/ + (box.getSize().y - outputStr.getLocalBounds().height) / 2
            );

    }

    sf::RectangleShape box;
    sf::Text outputStr;
    sf::String inputStr;
    sf::Vector2f positionVector;
    sf::Color grayColor;
    std::string logStr; /*for writing user input to terminal*/

    std::function<void()> onClick;


};