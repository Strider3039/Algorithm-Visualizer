#include "Avl.hpp"
#include "Stack.hpp"
#include "menuItems.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
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

    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Text title;
    mainMenuScreen(background, backgroundTexture, title, font, window);
    
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

        window.draw(background);
        window.draw(background);
        window.draw(title);

        for (auto& buttonItr : buttons)
        {
            window.draw(buttonItr);
        }

        window.display();
        window.clear();

    }

    return 0;
}
