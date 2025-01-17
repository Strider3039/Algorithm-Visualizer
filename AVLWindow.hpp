#include "BSTWindow.hpp"
#include "GraphicAvl.hpp"
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
          isRunning(true)
    {
        this->avl = GraphicAVL<T>(this->windowWidth, this->windowHeight); // Initialize the BST
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



};