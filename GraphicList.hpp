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

class GraphicList
{
public:
    GraphicList() {}
    GraphicList(sf::Vector2i screenDimensions) : screenDimensions(screenDimensions)
    {
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "Failed to load font" << std::endl;
        }
        loadColors(colors);
    }

    void clearData()
    {
        nodes.clear();
        UI.clear();
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

    /*returns true if window must be closed, false otherwise*/
    bool handleEvents(sf::RenderWindow& window, sf::Event& event)
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

            handleNodeInteractions(window, event);
        }
        return false;
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

    void handleTextInput(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& itr)
    {
        if (itr.second.scrollAndClick(event, window))
        {
            resetEvent(event);
            // while were still in the text box
            while (event.type != sf::Event::MouseButtonPressed)
            {
                if (window.pollEvent(event) && event.type == sf::Event::TextEntered)
                {
                     if (event.text.unicode == 27 /*|| event.text.unicode == 13*/) /* Escape or Enter */
                        break;
                    if (event.text.unicode == 13)
                        return;

                    itr.second.write(event.text.unicode, window);
                    resetEvent(event);
                }
                render(window);
            }
        }
    }

    void handleButtons(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& itr)
    {
        if (itr.first.scrollAndClick(event, window))
        {
            // did the insert button get clicked?
            if (itr.first._getStr() == "Insert")
               insert(itr);
            // did the remove button get clicked?
            if (itr.first._getStr() == "Remove")
                remove(itr);
        }
    }

    void remove(std::pair<Button, TextBox>& itr)
    {
        std::string str = itr.second._getText();
        cout << "Removing: " << str << endl;

        if (str == "type here")
            return;

        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].getText() == str)
            {
                nodes.erase(nodes.begin() + i);
                --i;
            }
        }
    }

    void insert(std::pair<Button, TextBox>& itr)
    {
        if (checkInput(itr))
        {
            cout << "ERROR: Invalid Input" << endl;
            return;
        }

        std::cout << "Inserting: " << itr.second._getText() << std::endl;
        Button newNode(itr.second._getText(), font, sf::Vector2f(500, 500), 100);
        Particle newParticle(newNode._getPosition().x, newNode._getPosition().y, 5, 5, newNode);
        newParticle.setDirection(sf::Vector2i(1, 1));
        nodes.push_back(newParticle);
    }

    bool checkInput(std::pair<Button, TextBox>& itr)
    {
        if (itr.second._getText() == "type here")
            return true;
        else
            return false;
    }

    void render(sf::RenderWindow& window)
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


    void drawNodes(sf::RenderWindow& window)
    {
        drawEdges(window);

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

    void resetEvent(sf::Event& event)
    {
        event = emptyEvent;
    }

    void drawEdges(sf::RenderWindow& window)
    {
        if (nodes.empty())
        {
            return;
        }
        for (int i = 0; (i + nodes.begin()) != nodes.end() - 1; i++)
        {
            sf::Vertex line[] = {
                 sf::Vertex(nodes[i].getPos(), sf::Color::Black),
                 sf::Vertex(nodes[i + 1].getPos(), sf::Color::Black),
            };
            window.draw(line, 2, sf::Lines);
        }

    }

    Colors colors;

    sf::Vector2i screenDimensions;
    sf::Font font;
    std::vector<std::pair<Button, TextBox>> UI;
    std::vector<Particle> nodes;
    sf::Event emptyEvent;

    sf::Vector2i mouseDirVec;
    sf::Vector2f mouseVelocity;
    sf::Vector2i previousMousePos;

    sf::Clock clock;
    float deltaTime;
};