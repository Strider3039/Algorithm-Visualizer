#include "Avl.hpp"
#include "Stack.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <X11/Xlib.h>
#include "newButton.hpp"

int main(void)
{

    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display!" << std::endl;
        return -1;
    }
    
    Screen* screen = DefaultScreenOfDisplay(display);
    int width = screen->width;
    int height = screen->height;

    std::cout << "Screen width: " << width << std::endl;
    std::cout << "Screen height: " << height << std::endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "Algorithm Visualizer", sf::Style::Fullscreen);


    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
    
    Button obj("Default string", font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(obj); 
        window.display();
        window.clear();

    }

    return 0;
}
