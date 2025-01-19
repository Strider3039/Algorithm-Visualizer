#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "menuItems.hpp"
#include "textBox.hpp"

// trying a completely new design for the trees. Stuff is not working properly

template <class T>
class GraphicTree {
public:

    struct TreeNode
    {
        T data;
        TreeNode* pLeft;
        TreeNode* pRight;
        sf::CircleShape shape;
        sf::Text text;
        sf::Vector2f position;

        

        TreeNode(T data, sf::Font& font, float xPos, float yPos)
        : data(data), pLeft(nullptr), pRight(nullptr)
        {
            // node visuals
            shape.setRadius(20);
            shape.setFillColor(sf::Color::Black);
            shape.setOutlineColor(sf::Color::White);
            shape.setOutlineThickness(5);
            position = {xPos, yPos};
            shape.setPosition(xPos, yPos);

            // text visuals
            text.setFont(font);
            text.setString(std::to_string(data));
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::White);
            auto bounds = text.getLocalBounds();
            text.setPosition(xPos + shape.getRadius() - bounds.width / 2, yPos + shape.getRadius() - bounds.height);
        }

    };


    virtual void insert(T data, TreeNode*& pNode, float xPos, float yPos, float offset, sf::Font& font)
    {
        if (pNode == nullptr)
        {
            pNode = new TreeNode(data, font, xPos, yPos);  // Link the new node
            return;
        }

        if (data < pNode->data)
        {
            insert(data, pNode->pLeft, xPos - offset, yPos + 150, offset / 2, font);
        }
        else if (data > pNode->data)
        {
            insert(data, pNode->pRight, xPos + offset, yPos + 150, offset / 2, font);
        }
    };
    virtual void remove(const T& value) = 0;
    virtual void reset() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};


template <class T>
class TreeWindow {
public:
    TreeWindow(float width, float height, sf::Font& font)
        : windowWidth(width), windowHeight(height), mFont(font), isRunning(true) {
        loadColors(colors);
    }

    void runVisual(sf::RenderWindow& window) {
        loadButtonUI(UI, mFont, windowWidth, windowHeight, colors);

        while (window.isOpen()) {
            processEvents(window);
            render(window);

            if (!isRunning) {
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
    bool isRunning;
    std::vector<std::pair<Button, TextBox>> UI;
    sf::Event emptyEvent;
    Colors colors;

    // Polymorphic Graphic Tree Pointer
    GraphicTree<T>* tree;

    virtual void initializeTree() = 0; // To be implemented by derived classes

    void processEvents(sf::RenderWindow& window) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::KeyPressed) 
            {
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
            while (event.type != sf::Event::MouseButtonPressed) 
            {
                if (window.pollEvent(event) && event.type == sf::Event::TextEntered) 
                {
                    if (event.text.unicode == 27 /* Escape */ || event.text.unicode == 13 /* Enter */)
                        break;

                    itr.second.write(event.text.unicode, window);
                    resetEvent(event);
                }
                render(window);
            }
        }
    }

    void resetEvent(sf::Event& event) {
        event = emptyEvent;
    }

    void handleButtons(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& itr) 
    {
        std::string buttonStr = itr.first._getStr();
        std::string inputStr = itr.second._getText();

        if (itr.first.scrollAndClick(event, window)) 
        {
            if (!inputStr.empty() && std::all_of(inputStr.begin(), inputStr.end(), ::isdigit)) 
            {
                if (buttonStr == "Insert") 
                {
                    tree->insert(std::stoi(inputStr), mFont);
                }

                if (buttonStr == "Remove") 
                {
                    tree->remove(std::stoi(inputStr));
                }
            }
        }
    }

    virtual void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) = 0;

    virtual void render(sf::RenderWindow& window) 
    {
        window.clear(colors.backgroundElementsColor);
        tree->draw(window);
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
