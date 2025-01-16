#pragma once
#include "GraphicBST.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include "menuItems.hpp"
#include "textBox.hpp"

template <class T>
class BSTWindow {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : windowWidth(width), windowHeight(height), mFont(font) {
        bst = GraphicBST<T>(windowWidth, windowHeight); // Initialize the BST
        backgroundColor.r = 233;
        backgroundColor.g = 236;
        backgroundColor.b = 239;
        background.setFillColor(backgroundColor);
        background.setSize(sf::Vector2f(windowWidth, windowHeight));
        isRunning = true;
    }

    void runVisual(sf::RenderWindow& window) {
        
        loadBstUI(UI, mFont, windowWidth, windowHeight);

        while (window.isOpen())
        {
            processEvents(window);
            render(window);

            if (isRunning == false)
            {
                isRunning = true;
                return;
            }
        }
    }

private:
    double windowWidth;
    double windowHeight;
    sf::Font mFont;
    sf::RectangleShape background;
    sf::Color backgroundColor;
    GraphicBST<T> bst;
    bool isRunning;
    vector<std::pair<Button, TextBox>> UI;

    void processEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code, window);
            }

        }
    }

    void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) {
        switch (key) {
            case sf::Keyboard::Num1:
                bst.insert(20, mFont);
                bst.insert(7, mFont);
                bst.insert(16, mFont);
                bst.insert(3, mFont);
                bst.insert(19, mFont);
                bst.insert(12, mFont);
                bst.insert(5, mFont);
                bst.insert(8, mFont);
                bst.insert(11, mFont);
                bst.insert(35, mFont);
                bst.insert(14, mFont);
                bst.insert(23, mFont);
                bst.insert(28, mFont);
                bst.insert(18, mFont);
                break;
            case sf::Keyboard::R:
                bst = GraphicBST<T>(windowWidth, windowHeight); // Reset the BST
                break;
            case sf::Keyboard::Escape:
                std::cout << "Returning to menu..." << std::endl;
                isRunning = false;
                break;
            default:
                break;
        }
    }

    void render(sf::RenderWindow& window) {
        window.clear();
        window.draw(background);
        bst.draw(window);
        drawUI(window);
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
};
