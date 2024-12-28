#include "Avl.hpp"
#include "Stack.hpp"
#include "menuItems.hpp"
#include "listWindow.hpp"
#include "BSTWindow.hpp"
#include "GraphicList.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <vector>

int main(void)
{  
    Display* display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display!" << std::endl;
        return -1;
    }

    if (!XineramaIsActive(display)) {
        std::cerr << "Xinerama is not active!" << std::endl;
        XCloseDisplay(display);
        return -1;
    }

    int screenCount;
    XineramaScreenInfo* screens = XineramaQueryScreens(display, &screenCount);

    if (screens == nullptr) {
        std::cerr << "Failed to query screens!" << std::endl;
        XCloseDisplay(display);
        return -1;
    }

    std::cout << "Number of physical screens: " << screenCount << std::endl;

    std::vector<double> screenWidths;
    std::vector<double> screenHeights;
    std::vector<int> screenXOffsets;
    std::vector<int> screenYOffsets;

    for (int i = 0; i < screenCount; ++i) {
        screenWidths.push_back(screens[i].width);
        screenHeights.push_back(screens[i].height);
        screenXOffsets.push_back(screens[i].x_org);
        screenYOffsets.push_back(screens[i].y_org);

        std::cout << "Screen " << i << ": "
                    << "Width = " << screens[i].width
                    << ", Height = " << screens[i].height
                    << ", X Offset = " << screens[i].x_org
                    << ", Y Offset = " << screens[i].y_org
                    << std::endl;
    }


    const int internalDisplay = 0;

    sf::RenderWindow window(sf::VideoMode(screenWidths[internalDisplay] , screenHeights[internalDisplay]), "Algorithm Visualizer", sf::Style::Default);
    window.setPosition(sf::Vector2i(screenXOffsets[internalDisplay], screenYOffsets[internalDisplay]));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Text title;

    GraphicList graphicListObj(sf::Vector2i(screenWidths[internalDisplay], screenHeights[internalDisplay]));
    BSTWindow<int> bst(screenWidths[internalDisplay], screenHeights[internalDisplay], font);

    mainMenuScreen(background, backgroundTexture, title, font, window);
    
    vector<Button> buttons;
    mainMenuItems(buttons, font, screenWidths[internalDisplay], screenHeights[internalDisplay]);

    

    while (window.isOpen()) 
    {
        if (screenCount > 1)
        {
            reSizeWindow(screenCount, screenWidths, screenHeights, screenXOffsets, window);
        }

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
                        graphicListObj.clearData();
                    }

                    if (buttonItr._getText() == "Binary Tree")
                    {
                        bst.runVisual(window);
                        
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
