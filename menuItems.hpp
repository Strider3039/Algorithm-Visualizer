#pragma once
#include "Button.hpp"
#include "textBox.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <X11/extensions/Xinerama.h>

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

inline void centerButtons(vector<Button>& buttons, sf::RenderWindow& window)
{
    int i = 7;
    for (auto& itr : buttons)
    {
        itr.getBox().setPosition(itr._getPosition());
       // itr._setPosititon(sf::Vector2f((window.getSize().x / 2), i*window.getSize().y / 15));
        cout << "button pos: " << itr._getPosition().x << endl;
        cout << "box pos: " << itr.getBox().getPosition().x << endl;
        cout << "text pos " << itr._getText().getPosition().x << endl;
        i++;
    }
}

 inline void reSizeWindow(const int screenCount, XineramaScreenInfo* screens, sf::RenderWindow &window, vector<Button>& buttons)
{
    for (int i = 0; i < screenCount - 1; i++) 
    { 
      if (window.getPosition().x <= screens[i].x_org - 50 && window.getSize().x == screens[i].width) 
      {
        window.setSize(sf::Vector2u(screens[i + 1].width, screens[i + 1].height));
        //centerButtons(buttons, window);
      }
      if (window.getPosition().x >= screens[i].x_org - 50 && window.getSize().x == screens[i + 1].width) 
      {
        window.setSize(sf::Vector2u(screens[i].width, screens[i].height));
        //centerButtons(buttons, window);
      }
    }
}



inline void loadListUI(vector<std::pair<Button, TextBox>>& UI, sf::Font& font, double screenWidth, double screenHeight)
{
    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    TextBox backField;

    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02), 250);
    TextBox insertField("type here", font, sf::Vector2f(screenWidth * .29, screenHeight * .02));
    
    Button remove("Remove", font, sf::Vector2f(screenWidth * .5, screenHeight * .02), 250);
    TextBox removeField("type here", font, sf::Vector2f(screenWidth * .59, screenHeight * .02));

    std::pair<Button, TextBox> UIBack(back, backField);
    std::pair<Button, TextBox> UIInsert(insert, insertField);
    std::pair<Button, TextBox> UIRemove(remove, removeField);


    UI.push_back(UIBack);
    UI.push_back(UIInsert);
    UI.push_back(UIRemove);
}

inline void loadBstUI(vector<std::pair<Button, TextBox>>& UI, sf::Font& font, double screenWidth, double screenHeight)
{
    // make back button textbox
    Button back("Back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    TextBox backField;

    // make insert button and textbox
    TextBox insertField("type here", font, sf::Vector2f(screenWidth * .2, screenHeight * .02));
    Button insert("Insert", font, sf::Vector2f(screenWidth * .29, screenHeight * .02), 250);

    Button remove("Remove", font, sf::Vector2f(screenWidth * .59, screenHeight * .02), 250);
    TextBox removeField("type here", font, sf::Vector2f(screenWidth * .5, screenHeight * .02));
}