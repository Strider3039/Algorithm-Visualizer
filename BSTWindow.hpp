#pragma once
#include "GraphicBST.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

template <class T>
class BSTWindow {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : windowWidth(width), windowHeight(height), mFont(font) {
        bst = GraphicBST<T>(windowWidth, windowHeight); // Initialize the BST
        background.setFillColor(sf::Color::White);
        background.setSize(sf::Vector2f(windowWidth, windowHeight));
    }

    void runVisual(sf::RenderWindow& window) {
        
        while (window.isOpen())
        {
            processEvents(window);
            render(window);
        }
    }

private:
    float windowWidth;
    float windowHeight;
    sf::Font& mFont;
    sf::RectangleShape background;
    GraphicBST<T> bst;

    void processEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
    }

    void handleKeyPress(sf::Keyboard::Key key) {
        switch (key) {
            case sf::Keyboard::Num1:
                bst.insert(10, mFont);
                break;
            case sf::Keyboard::R:
                bst = GraphicBST<T>(windowWidth, windowHeight); // Reset the BST
                break;
            case sf::Keyboard::Escape:
                std::cout << "Returning to menu..." << std::endl;
                
                break;
            default:
                break;
        }
    }

    void render(sf::RenderWindow& window) {
        window.clear();
        window.draw(background);
        bst.draw(window);
        window.display();
    }
};
