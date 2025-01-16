#pragma once
#include "linkedList.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <atomic>
#include "nodeGraphic.hpp"
#include "Button.hpp"
#include "menuItems.hpp"
#include "textBox.hpp"
//#include "UImodule.hpp"
#include "GravitySim.hpp"

/**************************************************************************************************
***************************************************************************************************

THIS FILE IS NO LONGER USED IN ANY WAY. "GraphicList.hpp" REPLACES IT.


sorry for yelling in caps lol, just want to make sure you see this
***************************************************************************************************
***************************************************************************************************/

class GraphicLinkedList
{
public:

    GraphicLinkedList() {}
    GraphicLinkedList(double width, double height) {
        screenWidth = width;
        screenHeight = height;
        background.setFillColor(sf::Color::White);
        background.setSize(sf::Vector2f(screenWidth, screenHeight));

        if (!font.loadFromFile("arial.ttf")) {

            cout << "Failed to load font" << endl;   
        }

        list = LinkedList<Button>();
    }

    void clearData() {
        UI.clear();
        list.clear();
        numItems = 0;
    }

    void loadGravSource()
    {
        source.setPos(sf::Vector2f (800, 500));
        source.setStrength(7000);
        source.setColor(sf::Color::Green);
        source.setRadius(8);
    }
 
    void loadParticle()
    {
        // particle.setPos(sf::Vector2f(700, 500));
        // particle.setVel(sf::Vector2f(4, 0));
        // particle.setColor(sf::Color::Magenta);
        // particle.setRadius(8);
    }

    void runVisual(sf::RenderWindow& window) {

       // loadListUI(UI, font, screenWidth, screenHeight);
        loadGravSource();
        loadParticle();


        while (window.isOpen()) {

            window.clear();  

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    return;
                }


                for (auto& itr : UI) {
                    if (itr.first.scrollAndClick(event, window)) {

                        if (itr.first._getStr() == "back") {
                            return;
                        }
                        if (itr.first._getStr() == "Insert") {


                            /*functionality of insert button*/
                            cout << "inserting: " << itr.second._getText() << endl;
                            list.insertFront
                            (
                                Button(itr.second._getText(), font, 
                                sf::Vector2f( (screenWidth / 2) + numItems * 200, screenHeight / 2), 150)
                            );
                            numItems++;
                        }
                    }
                    if (itr.second.scrollAndClick(event, window)) {

                        event = emptyEvent;

                        while (event.type != sf::Event::MouseButtonPressed) {

                            window.clear();
                            window.pollEvent(event);

                            if (event.type == sf::Event::TextEntered) {

                                if (event.text.unicode == 27 || event.text.unicode == 13)
                                {
                                    break;
                                }

                                itr.second.write(event.text.unicode, window);

                                /*reset event type*/
                                event = emptyEvent; 
                            }


                            for (auto& itr : UI) {
                                window.draw(itr.first);
                                window.draw(itr.second);
                            }

                            list.draw(window);
                            //particle.update_physics(sf::Mouse::getPosition());
                            source.render(window);
                            //particle.render(window);
                            window.display();
                        }


                        /*
                        
                        */
                    }
                }         
            }


            for (auto& itr : UI) {
                window.draw(itr.first);
                window.draw(itr.second);
            }

            //particle.update_physics(sf::Mouse::getPosition());
            source.render(window);
            //particle.render(window);

            list.draw(window);
            window.display();
        }
    }

private:

    void updatePhysics()
    {

    }

    double screenWidth;
    double screenHeight;
    
    LinkedList<Button> list;
    sf::RectangleShape background;
    sf::Font font;
    vector<std::pair<Button, TextBox>> UI;
    sf::Event event;
    sf::Event emptyEvent;
    int numItems;

    GravitySource source;
    //Particle particle;
};