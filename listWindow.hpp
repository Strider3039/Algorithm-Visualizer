#pragma once
#include "linkedList.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <atomic>
#include "nodeGraphic.hpp"
#include "Button.hpp"
#include "menuItems.hpp"
#include "textBox.hpp"
//#include "UImodule.hpp"

class GraphicLinkedList
{
public:
GraphicLinkedList() {}
GraphicLinkedList(double width, double height) 
{
    screenWidth = width;
    screenHeight = height;

    /*
    initialize background
    */
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(screenWidth, screenHeight));
    /*
    load font
    */
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
}

void clearData()
{
    // UIButtonVec.clear();
    // UITextBoxVec.clear();
    UI.clear();
}


void runVisual(sf::RenderWindow& window)
{
    loadListUI(UI, font, screenWidth, screenHeight);

    while (window.isOpen()) 
    {
        /*
        draw background before anything
        */
        window.draw(background);


        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                return;
            }

            for (auto& itr : UI)
            {
                if (itr.first.scrollAndClick(event, window))
                {

                    if (itr.first._getText() == "back") 
                    {
                        return;
                    }
                    if (itr.first._getText() == "Insert")
                    {
                        /*
                        functionality of insert button
                        */
                        cout << itr.second._getText() << endl;
                    }
                }

                if (itr.second.scrollAndClick(event, window))
                {
                    event = emptyEvent;
                    while (event.type != sf::Event::MouseButtonPressed) /*this condition allows the user to move mouse cursor wihtout breaking interaction*/
                    {
                        window.pollEvent(event);
                        if (event.type == sf::Event::TextEntered)
                        {
                            itr.second.write(event.text.unicode, window);

                            event = emptyEvent; /*need to reset event type. otherwise will read as TextEntered event for many loop iterations*/
                        }

                        window.clear();
                        window.draw(background);
                        for (auto& itr : UI)
                        {
                            window.draw(itr.first);
                            window.draw(itr.second);
                        }
                        window.display();
                    }
                }
            }





         
        }

        for (int i = 0; i < UI.size(); i++)
        {
            window.draw(UI[i].first);
            window.draw(UI[i].second);
        }

        /*
        draw text inputed by user
        */       
        window.display();
        window.clear();  
    }
}

private:

double screenWidth;
double screenHeight;

LinkedList<GNode> list; /* list of GNode's (same thing as button, different name for clarity)*/
sf::RectangleShape background;
sf::Font font;

vector<std::pair<Button, TextBox>> UI;

sf::Event event;
sf::Event emptyEvent;
};