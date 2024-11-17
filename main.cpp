#include "Avl.hpp"
#include "Stack.hpp"
#include "menuItems.hpp"
#include <utility>

int main(void)
{

    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display!" << std::endl;
        return -1;
    }
    
    Screen* screen = DefaultScreenOfDisplay(display);
    double screenWidth = screen->width;
    double screenHeight = screen->height;

    std::cout << "Screen width: " << screenWidth << std::endl;
    std::cout << "Screen screenHeight: " << screenHeight << std::endl;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Algorithm Visualizer", sf::Style::Fullscreen);


    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }

    // Load PNG background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("AV Background.png")) {
        std::cerr << "Failed to load background image" << std::endl;
        return -1;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale background to fit the window
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    // backgroundSprite.setScale(
    //     screenWidth / textureSize.x,
    //     screenHeight / textureSize.y
    // );
    
    vector<Button> buttons;
    mainMenuItems(buttons, font, screenWidth, screenHeight);

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            for (auto& buttonItr : buttons)
            {
                buttonItr.scrollAndClick(event, window);
            }
        }

        window.draw(backgroundSprite);

        for (auto& buttonItr : buttons)
        {
            window.draw(buttonItr);
        }

        window.display();
        window.clear();

    }

    return 0;
}
