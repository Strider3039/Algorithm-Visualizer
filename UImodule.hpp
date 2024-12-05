#pragma once
#include "Header.hpp"
#include "Button.hpp"
#include "textBox.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

class UImodule : public sf::Drawable
{
public:
UImodule() {}
UImodule(sf::Vector2f position, sf::Vector2f _screenBounds, sf::String _label)
{
    modulePosition = position;
    screenBounds = _screenBounds;
    label = _label;


    setPosition(position);

}
/*
set psotion of module. position of buttonComponent is based off positon of textFieldComponent
*/
void setPosition(sf::Vector2f position)
{
    modulePosition = position;

    /*
    set position of textBox obj
    */
    textFieldComponent._setPosititon(position);
    /*
    set position of button obj based off textBox posititon
    */
    buttonComponent._setPosititon(sf::Vector2f(textFieldComponent._getBounds().width, textFieldComponent.getPosition().y));

}

sf::Vector2f getPosition()
{
    return modulePosition;
}

protected:

virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
{
    target.draw(buttonComponent, states);
    target.draw(textFieldComponent, states);
}


private:

Button buttonComponent;
TextBox textFieldComponent;
sf::String label;

sf::Vector2f modulePosition; /*contains position of textFieldComponent*/
sf::Vector2f screenBounds;

};