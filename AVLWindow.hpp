#include "BSTWindow.hpp"
#include "GraphicAvl.hpp"
#include "GraphicBST.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


template <class T>
class AVLWindow : BSTWindow<T>
{
public:
        AVLWindow(float width, float height, sf::Font& font)
        : BSTWindow<T>(width, height, font), // Call the base class constructor
          windowWidth(width),
          windowHeight(height),
          mFont(font),
          avl(width, height),
          isRunning(true)
    {
        loadColors(this->colors);
    }

    void runvisual(sf::RenderWindow& window)
    {
        BSTWindow<T>::runVisual(window);
    }

private:
    float windowWidth;
    float windowHeight;
    sf::Font& mFont;
    bool isRunning;
    GraphicAVL<T> avl;



    void handleButtons(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& itr) override
    {
        string buttonStr = itr.first._getStr();
        string inputStr = itr.second._getText();

        if (itr.first.scrollAndClick(event, window))
        {
            // make sure string is valid for stoi
            if (!inputStr.empty() && std::all_of(inputStr.begin(), inputStr.end(), ::isdigit))
            {
                // did the insert button get clicked?
                if (buttonStr == "Insert")
                {
                    avl.insert(stoi(inputStr), mFont);
                    
                }
                    

                // did the remove button get clicked?
                if (buttonStr == "Remove")
                {
                    avl.remove(stoi(inputStr));
                    
                }
                
            }
            
                
        }
    }

    void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) {
        switch (key) {
            case sf::Keyboard::Num1:
                avl.insert(20, mFont);
                avl.insert(7, mFont);
                avl.insert(16, mFont);
                avl.insert(3, mFont);
                avl.insert(19, mFont);
                avl.insert(12, mFont);
                avl.insert(5, mFont);
                avl.insert(8, mFont);
                avl.insert(11, mFont);
                avl.insert(35, mFont);
                avl.insert(14, mFont);
                avl.insert(23, mFont);
                avl.insert(28, mFont);
                avl.insert(18, mFont);
                break;
            case sf::Keyboard::R:
                avl.reset(); // Reset the BST
                break;
            case sf::Keyboard::Escape:
                std::cout << "Returning to menu..." << std::endl;
                isRunning = false;
                break;
            default:
                break;
        }
    }

    void render(sf::RenderWindow& window) override
    {
        window.clear(this->colors.backgroundElementsColor);
        avl.draw(window);
        BSTWindow<T>::drawUI(window);
        window.display();
    }

};