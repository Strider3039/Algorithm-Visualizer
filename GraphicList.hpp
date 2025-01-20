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

class GraphicList : public WindowBase<Particle>
{
public:
    GraphicList() : WindowBase<Particle>() {}
    GraphicList(sf::Vector2i screenDimensions) : WindowBase<Particle>(screenDimensions)
    {
        loadColors(colors);
        this->screenDimensions = screenDimensions;
    }

    void runVisual(sf::RenderWindow& window)
    {
        loadListUI(UI, font, screenDimensions.x, screenDimensions.y, colors);
        sf::Event event;

        while (window.isOpen())
        {
            if (handleEvents(window, event)) {return;}
            render(window);
        }
    }

private:

    /*returns true if window must be closed, false otherwise*/
    virtual bool handleEvents(sf::RenderWindow& window, sf::Event& event) override
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return true;

            if (UI[0].first.scrollAndClick(event, window))
                return true;

            for (auto& itr : UI)
            {
                handleTextInput(window, event, itr);
                handleButtons(window, event, itr);
            }

            handleNodeInteractions(window, event); //For list implementation
        }
        return false;
    }

    void handleColisions(sf::RenderWindow& window, Particle &itr)
    {
        /*
        check each node to see if it collides with screen bounds or other nodes

        case1: top of node intersects
        case2: right of node intersects
        */

        int widthOffset = 58;
        int heightOffset = 40;

        for (auto& itr2 : nodes)
        {
            /*case1*/
            if (itr2.getShape()._getBounds().contains(itr.getPos().x, itr.getPos().y + heightOffset))
            {
                itr.setVel_y(6);
                itr.setDirection_y(-1);

                itr2.setVel_y(6);
                itr2.setDirection_y(1);
            }
            /*case2*/
            if (itr2.getShape()._getBounds().contains(itr.getPos().x + widthOffset, itr.getPos().y))
            {
                itr.setVel_x(6);
                itr.setDirection_x(-1);

                itr2.setVel_x(6);
                itr2.setDirection_x(1);
            }
        }

        if (itr.getPos().x + widthOffset >= screenDimensions.x)
        {
            itr.setVel_x(6);
            itr.setDirection_x(-1);
        }
        else if (itr.getPos().x - widthOffset <= 0)
        {
            itr.setVel_x(6);
            itr.setDirection_x(1);
        }
        if (itr.getPos().y + heightOffset >= screenDimensions.y)
        {
            itr.setVel_y(6);
            itr.setDirection_y(-1);
        }
        else if (itr.getPos().y - heightOffset <= 0)
        {
            itr.setVel_y(6);
            itr.setDirection_y(1);
        }
    }

    void handleNodeInteractions(sf::RenderWindow& window, sf::Event& event)
    {
        for (auto& itr : nodes)
        {
            if (itr.interaction(event, window))
            {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                    if (currentMousePos != previousMousePos)
                    {
                        itr.setPos(sf::Vector2f(currentMousePos.x, currentMousePos.y));
                        updateNodeVectoring(currentMousePos);
                        previousMousePos = currentMousePos;
                    }
                    render(window);
                }
                itr.setVel(mouseVelocity);
                itr.setDirection(mouseDirVec);
            }
        }
    }

    // void insert(std::pair<Button, TextBox>& itr) override
    // {
    //     if (checkInput(itr))
    //     {
    //         cout << "ERROR: Invalid Input" << endl;
    //         return;
    //     }

    //     std::cout << "Inserting: " << itr.second._getText() << std::endl;
    //     Button newNode(itr.second._getText(), font, sf::Vector2f(500, 500), 100);
    //     newNode._setFillColor(colors.primaryText);
    //     newNode._setOutlineThickness(0);
    //     Particle newParticle(newNode._getPosition().x, newNode._getPosition().y, 12, 1.5, newNode); 
    //     newParticle.setDirection(sf::Vector2i(1, 1));
    //     nodes.push_back(newParticle);
    // }

    void render(sf::RenderWindow& window) override 
    {
        window.clear(colors.backgroundElementsColor);
        drawNodes(window);
        drawUI(window);
        updatePhysics(window);
        window.display();
    }

    void drawUI(sf::RenderWindow& window)
    {
        for (auto& itr : UI)
        {
            window.draw(itr.first);
            window.draw(itr.second);
        }
    }

    void drawNodes(sf::RenderWindow& window) override
    {
        drawEdges(window);
        updateHeadColor();

        for (auto& itr : nodes)
        {
            itr.render(window);
        }
    }

    void updatePhysics(sf::RenderWindow& window)
    {
        for (auto& itr : nodes)
        {
            handleColisions(window, itr);
            itr.acceleratePos();
        }
    }

    void updateNodeVectoring(const sf::Vector2i& currentPos)
    {
        sf::Vector2i displacement = currentPos - previousMousePos;

        if (displacement != sf::Vector2i(0, 0))
        {
            mouseDirVec = { std::signbit(displacement.x) ? -1 : 1, std::signbit(displacement.y) ? -1 : 1 };

            deltaTime = clock.restart().asSeconds();
            deltaTime *= 100;

            mouseVelocity.x = std::clamp(displacement.x / deltaTime, -6.0f, 6.0f);
            mouseVelocity.y = std::clamp(displacement.y / deltaTime, -6.0f, 6.0f);
        }
    }

    void updateHeadColor()
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
                    nodes[nodes.size() - 2].getShape()._setOutlineThickness(0);
                }
            }
        }
    }

    sf::Vector2i mouseDirVec;
    sf::Vector2f mouseVelocity;
    sf::Vector2i previousMousePos;
    sf::Clock clock;
    float deltaTime;
};