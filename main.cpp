#include "Stack.hpp"
#include "menuItems.hpp"
#include "listWindow.hpp"
#include "AVLWindow.hpp"
#include "GraphicList.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <vector>

int main(void)
{  
    Colors colors;
    loadColors(colors);

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
    int currentScreen;
    XineramaScreenInfo* screens = XineramaQueryScreens(display, &screenCount);

    if (screens == nullptr) {
        std::cerr << "Failed to query screens!" << std::endl;
        XCloseDisplay(display);
        return -1;
    }

    cout << "Number of physical screens: " << screenCount << endl;
    for (int i = 0; i < screenCount; ++i) {
        cout << "Screen " << i << ": "
        << "Width = " << screens[i].width
        << ", Height = " << screens[i].height
        << ", X Offset = " << screens[i].x_org
        << ", Y Offset = " << screens[i].y_org
        << endl;
    }

/*
-use this const to choose which display you want to open the program in. 0 is default (internal display). 
-ex: 1 would be the second display if it exists
-using window style Default to achieve this
-if you can figure out how the hell to get shit to properly resize then be my guest lol
*/
    const int internalDisplay = 0;

    sf::RenderWindow window(sf::VideoMode(screens[internalDisplay].width , screens[internalDisplay].height), "Algorithm Visualizer", sf::Style::Default);
    window.setPosition(sf::Vector2i(screens[internalDisplay].x_org, screens[internalDisplay].y_org));

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
    }
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Text title;

    GraphicList graphicListObj(sf::Vector2i(screens[internalDisplay].width, screens[internalDisplay].height));
    BSTWindow<int> bst(screens[internalDisplay].width, screens[internalDisplay].height, font);
    //AVLWindow<int> avl(screens[internalDisplay].width, screens[internalDisplay].height, font);

    mainMenuScreen(background, backgroundTexture, title, font, window, colors);
    
    vector<Button> buttons;
    mainMenuItems(buttons, font, window.getSize().x, window.getSize().y, colors);
    

    while (window.isOpen()) 
    {
       // officialy giving up on this im sick of it
        // if (screenCount > 1)
        // {
        //     currentScreen = reSizeWindow(screenCount, &*screens, window, buttons);
        //     //centerButtons(buttons, window);
        // }

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
                    cout << buttonItr._getStr() << " button pressed" << endl;

                    /*
                    linked list button pressed
                    */
                    if (buttonItr._getStr() == "Exit")
                    {
                        return 0;
                    }
                    if (buttonItr._getStr() == "Linked List")
                    {
                        graphicListObj.runVisual(window);
                        graphicListObj.clearData();
                    }

                    if (buttonItr._getStr() == "Binary Tree")
                    {
                        bst.runVisual(window);
                        
                    }

                    if (buttonItr._getStr() == "AVL Tree")
                    {
                        //avl.runVisual(window);
                    }
                }
            }
        }

        // window.draw(background);
        // window.draw(background);
        window.draw(title);

        for (auto& buttonItr : buttons)
        {
            window.draw(buttonItr);
        }

        window.display();
        window.clear(colors.backgroundElementsColor);

    }

    
    return 0;
}
