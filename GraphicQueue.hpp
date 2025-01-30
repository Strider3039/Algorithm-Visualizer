#pragma once
#include "GraphicList.hpp"
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

class GraphicQueue : public GraphicList
{
public:
    GraphicQueue() : GraphicList() {}
    GraphicQueue(sf::Vector2i screenDimensions) : GraphicList(screenDimensions, 0)
    {
        loadColors(colors);
        this->screenDimensions = screenDimensions;

        loadStackUI(UI, font, screenDimensions.x, screenDimensions.y, colors);
    }
    
private:



    void remove(std::pair<Button, TextBox>& itr) override
    {
        std::string str = itr.second._getText();
        cout << "Removing: " << str << endl;

        if (str == "type here")
            return;
        nodes.erase(nodes.end());
        count--;
    }

    virtual void insert(std::pair<Button, TextBox>& itr) override // this is the linked list version
    {
        if (checkInput(itr))
        {
            cout << "ERROR: Invalid Input" << endl;
            return;
        }

        std::cout << "Inserting: " << itr.second._getText() << std::endl;
        Button newNode(itr.second._getText(), font, sf::Vector2f(500, 500), 100);
        newNode._setFillColor(colors.primaryText);
        newNode._setOutlineThickness(0);
        Particle newParticle(newNode._getPosition().x, newNode._getPosition().y, 12, 1.5, newNode);
        nodes.insert(nodes.begin(), newParticle);
        //nodes.push_back(newNode);
        count++;
    }

    virtual void updateHeadColor() override
    {
        if (!nodes.empty())
        {
            if (nodes.size() == 1)
            {
                nodes[0].getShape()._setOutlineColor(colors.orangeAccent);
                nodes[0].getShape()._setOutlineThickness(3);
            }
            else
            {
                nodes[0].getShape()._setOutlineColor(colors.greenAccent);
                nodes[0].getShape()._setOutlineThickness(3);

                nodes[nodes.size() - 1].getShape()._setOutlineColor(colors.redAccent);
                nodes[nodes.size() - 1].getShape()._setOutlineThickness(2);

                if (nodes.size() > 2)
                {
                    nodes[1].getShape()._setOutlineThickness(0);
                }
            }
        }
    }

};