#pragma once
#include "linkedList.hpp"
#include "newButton.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/Vector2.hpp>


class GraphicLinkedList
{
public:
GraphicLinkedList() 
{
    screenHeight = double();
    screenWidth = double();
}
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

    LinkedList<Button> list;

    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02));
    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02));

    std::vector<Button> UIButtons;
    UIButtons.push_back(back);
    UIButtons.push_back(insert);





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