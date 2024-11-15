#include "Avl.hpp"
#include "Stack.hpp"
#include "newButton.hpp"
#include <SFML/System/Vector2.hpp>

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
    
    // implement attempt to input object close to center of screen
    Button obj("Linked List", font, sf::Vector2f(width / 2, height / 2));
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.draw(obj); 
        window.display();
        window.clear();

    }

    return 0;
}
