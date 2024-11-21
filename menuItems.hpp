#pragma once
#include "Button.hpp"


inline void mainMenuScreen(sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture, sf::Text& title, sf::Font& font, sf::Window& window)
{
    
    // Create Menu Title
    title = sf::Text("Algorithm Visualizer", font, 70);
    title.setStyle(sf::Text::Underlined | sf::Text::Bold);
    title.setFillColor(sf::Color::Cyan);

    // Center the title
    sf::Vector2u windowSize = window.getSize();
    title.setPosition(
        windowSize.x / 2.f - title.getLocalBounds().width / 2.f,
        5*windowSize.y / 20.f // Place it near the top
    );

    // load and initialize background file
    if (!backgroundTexture.loadFromFile("AV Background (2).png")) {
        std::cerr << "Failed to load background image" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);

    // Scale background to fit the window
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    windowSize = window.getSize();
}

inline void mainMenuItems(vector<Button>& buttons, sf::Font& font, double width, double height)
{
    Button list_button("Linked List", font, sf::Vector2f(width / 2, 7*height / 15), 250);
    Button queue_button("Queue", font, sf::Vector2f(width / 2, 8*height / 15), 250);
    Button stack_button("Stack", font, sf::Vector2f(width / 2, 9*height / 15), 250);
    Button bst_button("Binary Tree", font, sf::Vector2f(width / 2, 10*height / 15), 250);
    Button avl_button("AVL Tree", font, sf::Vector2f(width / 2, 11*height / 15), 250);

    buttons.push_back(list_button);
    buttons.push_back(queue_button);
    buttons.push_back(stack_button);
    buttons.push_back(bst_button);
    buttons.push_back(avl_button);

}

/*
user interface items for list

more items to be added
*/
inline void listUI(vector<Button>& buttons, sf::Font& font, double screenWidth, double screenHeight)
{
    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02), 250);

    buttons.push_back(back);
    buttons.push_back(insert);
}