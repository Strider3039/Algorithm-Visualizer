#pragma once
#include "GravitySim.hpp"
#include "Header.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <X11/X.h>
#include <cstdint>
#include <vector>
#include "Button.hpp"
#include "textBox.hpp"
#include "menuItems.hpp"
#include <algorithm>
#include "WindowBase.cpp"

class GraphicStack : public WindowBase<Particle>
{
public:
    GraphicStack() : WindowBase<Particle>() {}
    GraphicStack(sf::Vector2i screenDimensions) : WindowBase<Particle>(screenDimensions)
    {
        loadColors(colors);
        this->screenDimensions = screenDimensions;

        loadStackUI(UI, font, screenDimensions.x, screenDimensions.y, colors);
    }
    
private:

    void insert(std::pair<Button, TextBox>& itr) override
    {
        if (checkInput(itr))
        {
            std::cout << "ERROR: Invalid Input" << std::endl;
            return;
        }
        std::cout << "Inserting: " << itr.second._getText() << std::endl;
        Button newNode(itr.second._getText(), font, sf::Vector2f(500, 500), 300, 50);
        posCenterScreen(newNode);

        newNode._setFillColor(colors.primaryText);
        newNode._setOutlineThickness(0);

        Particle newParticle(newNode._getPosition().x, newNode._getPosition().y, 12, 1.5, newNode);
        nodes.push_back(newParticle);
        posStackFormat();
    }

    void remove(std::pair<Button, TextBox>& itr) override
    {
        std::string str = itr.second._getText();
        cout << "Removing: " << str << endl;

        if (str == "type here")
            return;
        nodes.erase(nodes.end());
        posStackFormat();

        for (auto& itr : nodes)
        {
            itr.setPos(sf::Vector2f(itr.getPos().x, itr.getPos().y - 200));
        }

        count--;
    }

    void posCenterScreen(Button &node)
    {
        node._setPosititon(sf::Vector2f(screenDimensions.x / 2.f - node._getBounds().width / 2.f, 5 * screenDimensions.y / 20.f));
    }

    void posStackFormat()
    {
        for (auto& itr : nodes)
        {
            itr.setPos(sf::Vector2f(itr.getPos().x, itr.getPos().y + 100));
        }
    }
};