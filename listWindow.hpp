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




void runVisual(sf::RenderWindow& window)
{
    // /*
    // text box for inserting function. will be replaced with vector of textBox's as more are added
    // */
    // TextBox textBox_insert("Insert", font, sf::Vector2f(800, 800));

    /*
    load UI textBox's
    */
    listUITextBox(UITextBoxVec, font, screenWidth, screenHeight);

    /*
    load UI buttons
    */
    listUIButtons(UIButtonVec, font, screenWidth, screenHeight);



    /*
    load testModule
    */
    //UImodule testModule(sf::Vector2f(600, 600), sf::Vector2f(screenWidth, screenHeight), "test");


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

            /*************************************************************************** */
            // if (textBox_insert.scrollAndClick(event, window))
            // {
            //     std::cout << "insert_textBox interaction!" << std::endl;
            //     /*
            //     while cursor intersects box, pollevents to chack for text entered.
            //     draw and display window to reflect updates to text box
            //     */
            //     //while (textBox_insert.cursorIntersect(window))
            //     event = emptyEvent;
            //     while (event.type != sf::Event::MouseButtonPressed) /*this condition allows the user to move mouse cursor wihtout breaking interaction*/
            //     {
            //         window.pollEvent(event);
            //         if (event.type == sf::Event::TextEntered)
            //         {
            //             textBox_insert.write(event.text.unicode, window);

            //             event = emptyEvent; /*need to reset event type. otherwise will read as TextEntered event for ages*/
            //         }
            //         window.clear();
            //         window.draw(background);
            //         window.draw(textBox_insert);
            //         for (auto& buttonItr : UIButtonVec)
            //         {
            //             window.draw(buttonItr);
            //         }
            //         window.display();
            //     }
            // }
            /******************************************************************************* */
            for (auto& buttonItr : UIButtonVec)
            {
                if (buttonItr.scrollAndClick(event, window))
                {
                    buttonItr.triggerCallback();

                    if (buttonItr._getText() == "back") /*this should be the only button i have to to this for*/
                    {
                        return;
                    }
                }
            }
            for (auto& textBoxItr : UITextBoxVec)
            {
                if (textBoxItr.scrollAndClick(event, window))
                {
                    textBoxItr.triggerCallback();
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
        for (auto& buttonItr : UIButtonVec)
        {
            window.draw(buttonItr);
        }
        /*
        draw textBox's
        */
        for (auto& textBoxItr : UITextBoxVec)
        {
            window.draw(textBoxItr);
        }

        /*
        draw text inputed by user
        */       
        //window.draw(input);
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

vector<Button> UIButtonVec;
vector<TextBox> UITextBoxVec;

sf::Event event;
sf::Event emptyEvent;
};