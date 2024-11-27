#include "Header.hpp"
#include "Button.hpp"
#include "textBox.hpp"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

class UImodule : public sf::Drawable
{
public:
UImodule() {}
UImodule(sf::Vector2f position, sf::Vector2f _screenBounds)
{
    modulePosition = position;
    screenBounds = _screenBounds;


}

void setPosition()
{
    //buttonComponent.
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
sf::Vector2f modulePosition;

sf::Vector2f screenBounds;
};