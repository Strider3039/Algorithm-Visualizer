#pragma once
#include "GraphicBST.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "menuItems.hpp"
#include "textBox.hpp"

template <class T>
class BSTWindow {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : windowWidth(width), windowHeight(height), mFont(font) {
        bst = GraphicBST<T>(windowWidth, windowHeight); // Initialize the BST
        isRunning = true;

        loadColors(colors);
    }

    void runVisual(sf::RenderWindow& window) {
        
        loadButtonUI(UI, mFont, windowWidth, windowHeight, colors);

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

protected:
    double windowWidth;
    double windowHeight;
    sf::Font mFont;
    sf::RectangleShape background;
    sf::Color backgroundColor;
    GraphicBST<T> bst;
    bool isRunning;
    vector<std::pair<Button, TextBox>> UI;
    sf::Event emptyEvent;
    Colors colors;
    

    void processEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code, window);
            }

            if (UI[0].first.scrollAndClick(event, window))
            {
                isRunning = false;
            }

           
            for (auto& itr : UI)
            {
                handleTextInput(window, event, itr);
                handleButtons(window, event, itr);
            }
            

        }
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

    void resetEvent(sf::Event& event)
    {
        event = emptyEvent;
    }

    virtual void handleButtons(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& itr)
    {
        string buttonStr = itr.first._getStr();
        string inputStr = itr.second._getText();

        if (itr.first.scrollAndClick(event, window))
        {
            // make sure string is valid for stoi
            if (!inputStr.empty() && std::all_of(inputStr.begin(), inputStr.end(), ::isdigit))
            {
                // did the insert button get clicked?
                if (buttonStr == "Insert")
                {
                    bst.insert(stoi(inputStr), mFont);
                    
                }
                    

                // did the remove button get clicked?
                if (buttonStr == "Remove")
                {
                    bst.remove(stoi(inputStr));
                    
                }
                
            }
            
                
        }
    }

    
    virtual void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) {
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
                bst.reset(); // Reset the BST
                break;
            case sf::Keyboard::Escape:
                std::cout << "Returning to menu..." << std::endl;
                isRunning = false;
                break;
            default:
                break;
        }
    }

    virtual void render(sf::RenderWindow& window) {
        window.clear(colors.backgroundElementsColor);
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
