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

template <class T>
class WindowBase
{
public:

    WindowBase() {}
    WindowBase(sf::Vector2i screenDimensions)
    {
        this->screenDimensions = screenDimensions;
        loadColors(colors);
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "Failed to load font" << std::endl;
        }
    }

    virtual void render(sf::RenderWindow& window)
    {
        window.clear(colors.backgroundElementsColor);
        drawNodes(window);
        drawUI(window);
        // updatePhysics(window); List implementation
        window.display();
    }
    virtual void drawNodes(sf::RenderWindow& window)
    {
        drawEdges(window);
       // updateHeadColor(); for list implementation

        for (auto& itr : nodes)
        {
            itr.render(window);
        }
    }

    /*returns true if window must be closed, false otherwise*/
    virtual bool handleEvents(sf::RenderWindow& window, sf::Event& event)
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

            // handleNodeInteractions(window, event); //For list implementation
        }
        return false;
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
            if (itr.first._getStr() == "Clear")
                clear(itr);
        }
    }

    virtual void insert(std::pair<Button, TextBox>& itr) // this is the linked list version
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
        newParticle.setDirection(sf::Vector2i(1, 1));
        nodes.push_back(newParticle);
        //nodes.push_back(newNode);
    }

    void clearData()
    {
        nodes.clear();
        UI.clear();
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

    bool checkInput(std::pair<Button, TextBox>& itr)
    {
        if (itr.second._getText() == "type here")
            return true;
        else
            return false;
    }

    void drawUI(sf::RenderWindow& window)
    {
        for (auto& itr : UI)
        {
            window.draw(itr.first);
            window.draw(itr.second);
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

    void clear(std::pair<Button, TextBox>& itr)
    {
        cout << "Clearing" << endl;
        nodes.clear();
    }

    /*
        *if it involves Particle, use <T>*

        Functions that are the same accross linked list, stack, and queue.
        Virtual functions are very slightly different but are here for organization

        1. virtual render function ---
        2. virtual handle Events ---
        3. handle text input ---
        4. handle buttons ---
        5. virtual insert ---
        6. remove ---
        7. check input ---
        8. draw UI ---
        9. virtual draw nodes // virtual becasue we update colors for list ---
        10. reset event ---
        11. draw edges ---
        12. clear ---

        Members:

        sf::Vector2i screenDimensions
        sf::Font font;
        std::vector<std::pair<Button, TextBox>> UI;
        std::Vector<T> nodes;   // T = Particle for linked lsit
        sf::Event emptyEvent;


    */

protected:

    sf::Vector2i screenDimensions;
    sf::Font font;
    std::vector<std::pair<Button, TextBox>> UI;
    std::vector<T> nodes;   // T = Particle for linked lsit
    sf::Event emptyEvent;
    Colors colors;
};