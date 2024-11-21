#pragma once
#include "linkedList.hpp"
#include <atomic>
#include "nodeGraphic.hpp"
#include "newButton.hpp"
#include "menuItems.hpp"
#include "textBox.hpp"

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




void runVisual(sf::RenderWindow& window)
{
    /*
    text box for inserting function. will be replaced with vector of textBox's as more are added
    */
    TextBox textBox_insert("Insert", font, sf::Vector2f(800, 800));

    /*
    load UI buttons
    */
    listUI(UIButtons, font, screenWidth, screenHeight);


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
            if (textBox_insert.scrollAndClick(event,window))
            {
                std::cout << "insert_textBox interaction!" << std::endl;
                /*
                while cursor intersects box, pollevents to chack for text entered.
                draw and display window to reflect updates to text box
                */
                while (textBox_insert.cursorIntersect(window))
                {
                    window.pollEvent(event);
                    if (event.type == sf::Event::TextEntered)
                    {
                        textBox_insert.write(event.text.unicode, window);

                        event = emptyEvent; /*need to reset event type. otherwise will read as TextEntered event for ages*/
                    }
                    window.clear();
                    window.draw(background);
                    window.draw(textBox_insert);
                    for (auto& buttonItr : UIButtons)
                    {
                        window.draw(buttonItr);
                    }
                    window.display();
                }
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

            /*THIS AREA IS FOR VISUALIZING LINKED LIST
            
            area above and below this is used for the userinterface / functionality and will change as more functions are added
            */

            /*
            THINGS TO NOTE
            the "insert" button and the "textBox_insert" will be used together to call 
            the insert operation from the linked list class. 


            */





         
        }
        /*
        draw buttons
        */
        for (auto& buttonItr : UIButtons)
        {
            window.draw(buttonItr);
        }
        /*
        draw text inputed by user
        */       
        //window.draw(input);
        window.draw(textBox_insert);
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
vector<Button> UIButtons;

sf::Event event;
sf::Event emptyEvent;
};