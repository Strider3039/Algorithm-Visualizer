#pragma once
#include "Button.hpp"

class GNode : public Button
{
    public:
    GNode() {}

    GNode(std::string _text, sf::Font& _font, sf::Vector2f position, double width) 
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

    protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
    {
        target.draw(box, states);
        target.draw(text, states);
    }

    private:

    sf::RectangleShape box;
    sf::Vector2f positionVector;
    double boxWidth;
    sf::Text text;


};


/*
this class exists for the sake of readability
*/