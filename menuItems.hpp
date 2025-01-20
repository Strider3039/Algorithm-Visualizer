#pragma once
#include "Button.hpp"
#include "textBox.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <X11/extensions/Xinerama.h>



struct Colors
{
    sf::Color UIelementsColor;  // Primary Blue	#007BFF
    sf::Color greenAccent;  // Secondary Green	#28A745
    sf::Color redAccent;    // Accent Red	#DC3545
    sf::Color primaryText;  // Neutral Dark Gray	#343A40
    sf::Color backgroundElementsColor;  // Neutral Light Gray	#E9ECEF
    sf::Color orangeAccent;     // Accent Orange  #D28A58.
};

inline void loadColors(Colors &colorsStruct)
{
    colorsStruct.UIelementsColor.r = 0;
    colorsStruct.UIelementsColor.g = 123;
    colorsStruct.UIelementsColor.b = 255;

    colorsStruct.greenAccent.r = 40;
    colorsStruct.greenAccent.g = 167;
    colorsStruct.greenAccent.b = 69;

    colorsStruct.redAccent.r = 220;
    colorsStruct.redAccent.g = 53;
    colorsStruct.redAccent.b = 69;

    colorsStruct.primaryText.r = 52;
    colorsStruct.primaryText.g = 58;
    colorsStruct.primaryText.b = 64;

    colorsStruct.backgroundElementsColor.r = 233;
    colorsStruct.backgroundElementsColor.g = 236;
    colorsStruct.backgroundElementsColor.b = 239;

    colorsStruct.orangeAccent.r = 210;
    colorsStruct.orangeAccent.g = 138;
    colorsStruct.orangeAccent.b = 88;
}

inline void mainMenuScreen(sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture, sf::Text& title, sf::Font& font, sf::Window& window, Colors colors)
{
    
    // Create Menu Title
    title = sf::Text("Algorithm Visualizer", font, 70);
    title.setStyle(sf::Text::Underlined | sf::Text::Bold);
    title.setFillColor(colors.primaryText);

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

inline void mainMenuItems(vector<Button>& buttons, sf::Font& font, double width, double height, Colors colors)
{
    Button list_button("Linked List", font, sf::Vector2f(width / 2, 7*height / 15), 250);
    list_button._setFillColor(colors.UIelementsColor);
    list_button._setOutlineColor(colors.primaryText);
    list_button._setOutlineThickness(1);
    Button queue_button("Queue", font, sf::Vector2f(width / 2, 8*height / 15), 250);
    queue_button._setFillColor(colors.UIelementsColor);
    queue_button._setOutlineColor(colors.primaryText);
    queue_button._setOutlineThickness(1);
    Button stack_button("Stack", font, sf::Vector2f(width / 2, 9*height / 15), 250);
    stack_button._setFillColor(colors.UIelementsColor);
    stack_button._setOutlineColor(colors.primaryText);
    stack_button._setOutlineThickness(1);
    Button bst_button("Binary Tree", font, sf::Vector2f(width / 2, 10*height / 15), 250);
    bst_button._setFillColor(colors.UIelementsColor);
    bst_button._setOutlineColor(colors.primaryText);
    bst_button._setOutlineThickness(1);
    Button avl_button("AVL Tree", font, sf::Vector2f(width / 2, 11*height / 15), 250);
    avl_button._setFillColor(colors.UIelementsColor);
    avl_button._setOutlineColor(colors.primaryText);
    avl_button._setOutlineThickness(1);
    Button exit_button("Exit", font, sf::Vector2f(width / 2, 12*height / 15), 250);
    exit_button._setFillColor(colors.UIelementsColor);
    exit_button._setOutlineColor(colors.primaryText);
    exit_button._setOutlineThickness(1);

    buttons.push_back(list_button);
    buttons.push_back(queue_button);
    buttons.push_back(stack_button);
    buttons.push_back(bst_button);
    buttons.push_back(avl_button);
    buttons.push_back(exit_button);
}

inline void centerButtons(vector<Button>& buttons, sf::RenderWindow& window)
{
    int i = 7;
    for (auto& itr : buttons)
    {
        itr._setPosititon(sf::Vector2f((window.getSize().x / 2), i*window.getSize().y / 15));

        cout << sf::Mouse::getPosition(window).x;
        cout << "button pos: " << itr._getPosition().x << endl;
        cout << "box pos: " << itr.getBox().getPosition().x << endl;
        cout << "text pos " << itr._getText().getPosition().x << endl;
        i++;
    }
}

 inline int reSizeWindow(const int screenCount, XineramaScreenInfo* screens, sf::RenderWindow &window, vector<Button>& buttons)
{
    for (int i = 0; i < screenCount - 1; i++) 
    { 
      if (window.getPosition().x <= screens[i].x_org - 50 && window.getSize().x == screens[i].width) /*window is in next screen*/
      {
        window.setSize(sf::Vector2u(screens[i + 1].width, screens[i + 1].height));
        return i + 1;
        //centerButtons(buttons, window);
      }
      if (window.getPosition().x >= screens[i].x_org - 50 && window.getSize().x == screens[i + 1].width) /*window is in prev screen*/
      {
        window.setSize(sf::Vector2u(screens[i].width, screens[i].height));
        return i;
        //centerButtons(buttons, window);
      }
    }
    return 0;
}

inline void loadListUI(vector<std::pair<Button, TextBox>>& UI, sf::Font& font, double screenWidth, double screenHeight, Colors colors)
{
    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    TextBox backField;
    back._setFillColor(colors.UIelementsColor);
    back._setOutlineColor(colors.primaryText);
    back._setOutlineThickness(1);

    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02), 250);
    TextBox insertField("type here", font, sf::Vector2f(screenWidth * .29, screenHeight * .02));
    insert._setFillColor(colors.UIelementsColor);
    insert._setOutlineColor(colors.primaryText);
    insert._setOutlineThickness(1);

    Button remove("Remove", font, sf::Vector2f(screenWidth * .5, screenHeight * .02), 250);
    TextBox removeField("type here", font, sf::Vector2f(screenWidth * .59, screenHeight * .02));
    remove._setFillColor(colors.UIelementsColor);
    remove._setOutlineColor(colors.primaryText);
    remove._setOutlineThickness(1);

    Button clear("Clear", font, sf::Vector2f(screenWidth * .8, screenHeight * .02), 250);
    TextBox clearField;
    clear._setFillColor(colors.UIelementsColor);
    clear._setOutlineColor(colors.primaryText);
    clear._setOutlineThickness(1);

    std::pair<Button, TextBox> UIBack(back, backField);
    std::pair<Button, TextBox> UIInsert(insert, insertField);
    std::pair<Button, TextBox> UIRemove(remove, removeField);
    std::pair<Button, TextBox> UIClear(clear, clearField);

    UI.push_back(UIBack);
    UI.push_back(UIInsert);
    UI.push_back(UIRemove);
    UI.push_back(UIClear);
}

inline void loadButtonUI(vector<std::pair<Button, TextBox>>& UI, sf::Font& font, double screenWidth, double screenHeight, Colors colors)
{
    Button back("back", font, sf::Vector2f(screenWidth * .055, screenHeight * .02), 250);
    TextBox backField;
    back._setFillColor(colors.UIelementsColor);
    back._setOutlineColor(colors.primaryText);
    back._setOutlineThickness(1);

    Button insert("Insert", font, sf::Vector2f(screenWidth * .2, screenHeight * .02), 250);
    TextBox insertField("type here", font, sf::Vector2f(screenWidth * .29, screenHeight * .02));
    insert._setFillColor(colors.UIelementsColor);
    insert._setOutlineColor(colors.primaryText);
    insert._setOutlineThickness(1);

    Button remove("Remove", font, sf::Vector2f(screenWidth * .5, screenHeight * .02), 250);
    TextBox removeField("type here", font, sf::Vector2f(screenWidth * .59, screenHeight * .02));
    remove._setFillColor(colors.UIelementsColor);
    remove._setOutlineColor(colors.primaryText);
    remove._setOutlineThickness(1);

    std::pair<Button, TextBox> UIBack(back, backField);
    std::pair<Button, TextBox> UIInsert(insert, insertField);
    std::pair<Button, TextBox> UIRemove(remove, removeField);

    UI.push_back(UIBack);
    UI.push_back(UIInsert);
    UI.push_back(UIRemove);
}