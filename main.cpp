#include "Avl.hpp"
#include "Stack.hpp"
#include "menuItems.hpp"
#include "listWindow.hpp"

int main(void)
{  
// hehe
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

    /*
    graphic linked list object.
    */
    GraphicLinkedList graphicListObj(screenWidth, screenHeight);

    mainMenuScreen(background, backgroundTexture, title, font, window);
    
    vector<Button> buttons;
    mainMenuItems(buttons, font, screenWidth, screenHeight);

    

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

            for (auto& buttonItr : buttons)
            {

                /*
                detects when and which button is pressed. flippin cool.
                */
                if (buttonItr.scrollAndClick(event, window))
                {
                    cout << buttonItr._getText() << " button pressed" << endl;

                    /*
                    linked list button pressed
                    */
                    if (buttonItr._getText() == "Linked List")
                    {
                        graphicListObj.runVisual(window);
                    }
                }
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
