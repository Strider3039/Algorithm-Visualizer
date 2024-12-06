#pragma once
#include "Button.hpp"
#include "textBox.hpp"
#include <SFML/System/Vector2.hpp>


inline void mainMenuScreen(sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture, sf::Text& title, sf::Font& font, sf::Window& window)
{
    
    // Create Menu Title
    title = sf::Text("Algorithm Visualizer", font, 70);
    title.setStyle(sf::Text::Underlined | sf::Text::Bold);
    title.setFillColor(sf::Color::White);

    // Center the title
    sf::Vector2u windowSize = window.getSize();
    title.setPosition(
        windowSize.x / 2.f - title.getLocalBounds().width / 2.f,
        5*windowSize.y / 20.f // Place it near the top
    );

    // load and initialize background file
    if (!backgroundTexture.loadFromFile("AV Background.png")) {
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
inline void listUIButtons(vector<Button>& buttonVec, sf::Font& font, double screenWidth, double screenHeight)
{
    /*
    buttons for UI
    */
    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02), 250);

    back.setCallback([]() 
    {
        std::cout << "Back button pressed" << std::endl;
    });

    buttonVec.push_back(back);
    buttonVec.push_back(insert);
}

inline void listUITextBox(vector<TextBox>& textBoxVec, sf::Font& font, double screenWidth, double screenHeight)
{
    /*
    textBox's for UI
    */
    TextBox insert("type here", font, sf::Vector2f(400, 400));

    textBoxVec.push_back(insert);

}