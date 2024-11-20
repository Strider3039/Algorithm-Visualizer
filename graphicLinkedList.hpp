#pragma once
#include "linkedList.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "nodeGraphic.hpp"
#include "newButton.hpp"
#include "menuItems.hpp"

class GraphicLinkedList
{
public:
GraphicLinkedList() {}
GraphicLinkedList(double width, double height) 
{
    screenWidth = width;
    screenHeight = height;
}


void runVisual(sf::RenderWindow& window)
{
    /*
    load font
    */
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }

    LinkedList<GNode> list;

    vector<Button> UIButtons;
    listUI(UIButtons, font, screenWidth, screenHeight);


        /*
        variables for basic text input logic
        */
        sf::Text input;
        input.setFont(font);
        input.setFillColor(sf::Color::White);
        input.setPosition((sf::Vector2f(500, 500)));
        sf::String str;
        std::string stdStr;


    while (window.isOpen()) 
    {
        sf::Event event;
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

            for (auto& buttonItr : UIButtons)
            {
                if (buttonItr.scrollAndClick(event, window))
                {
                    std::cout << buttonItr._getText() << " button pressed" << std::endl;
                    
                    if (buttonItr._getText() == "back")
                    {
                        return;
                    }
                }
            }


/*
basic text input logic -- definitely needs to be moved, its here just for testing purposes
*/

                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == 8)
                    {
                        str.erase(str.getSize()-1);
                        stdStr = str;
                        cout << stdStr << endl;
                        input.setString(str);
                    }
                    else 
                    {               
                        str += event.text.unicode;
                        stdStr = str;
                        cout << stdStr << endl;
                        input.setString(str);
                    }
                }
            

            window.draw(input);














        /*
        draw buttons
        */
        for (auto& buttonItr : UIButtons)
        {
            window.draw(buttonItr);
        }

            window.display();
            window.clear();           
        }
    }
}

private:

double screenWidth;
double screenHeight;
};