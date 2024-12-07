#pragma once
#include "linkedList.hpp"
#include <SFML/Graphics/Color.hpp>
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
#include "GravitySim.hpp"

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

    // GravitySource source(800, 500, 7000);

    void loadGravSource()
    {
        source.setPos(sf::Vector2f (800, 500));
        source.setStrength(7000);
    }
 
    void loadParticle()
    {
        particle.setPos(sf::Vector2f(600, 700));
        particle.setVel(sf::Vector2f(4, 0));
        particle.setColor(sf::Color::Magenta);
        particle.setRadius(8);
    }

    void runVisual(sf::RenderWindow& window) {

        loadListUI(UI, font, screenWidth, screenHeight);
        loadGravSource();
        loadParticle();


        while (window.isOpen()) {

            window.clear();  

            //window.draw(background);

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    return;
                }


                for (auto& itr : UI) {
                    if (itr.first.scrollAndClick(event, window)) {

                        if (itr.first._getText() == "back") {
                            return;
                        }
                        if (itr.first._getText() == "Insert") {


                            /*functionality of insert button*/
                            cout << "inesrting: " << itr.second._getText() << endl;
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
                                itr.second.write(event.text.unicode, window);

                                /*reset event type*/
                                event = emptyEvent; 
                            }


                            for (auto& itr : UI) {
                                window.draw(itr.first);
                                window.draw(itr.second);
                            }

                            //window.draw(background);
                            list.draw(window);
                            particle.update_physics(source);
                            source.render(window);
                            particle.render(window);
                            window.display();
                        }
                    }
                }         
            }


            for (auto& itr : UI) {
                window.draw(itr.first);
                window.draw(itr.second);
            }

            particle.update_physics(source);
            source.render(window);
            particle.render(window);

            list.draw(window);
            window.display();
        }
    }

private:

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
    Particle particle;
};