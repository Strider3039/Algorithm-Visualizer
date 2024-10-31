#include "Avl.hpp"
#include "Stack.hpp"
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>

int main(void)
{

    

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Algorithm Visualizer");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
