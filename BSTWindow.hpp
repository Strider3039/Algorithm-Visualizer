#include "GraphicBST.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>

template <class T>
class BSTWindow : public TreeWindow<T> {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : TreeWindow<T>(width, height, font) 
    {
        this->tree = new GraphicBST<T>(this->windowWidth, this->windowHeight, this->mFont);
    }

    ~BSTWindow() {
        delete this->tree;
    }

private:

    // use if needed
    void initializeTree() override 
    {
    }

    void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) override
    {
        switch (key)
        {
        case sf::Keyboard::Num1: // Insert test values
            this->tree->insert(10, this->mFont);
            this->tree->insert(20, this->mFont);
            this->tree->insert(5, this->mFont);
            this->tree->insert(15, this->mFont);
            this->tree->insert(25, this->mFont);
            this->tree->insert(30, this->mFont);
            this->tree->insert(40, this->mFont);
            this->tree->insert(50, this->mFont);
            this->tree->insert(60, this->mFont);
            this->tree->insert(70, this->mFont);
            this->tree->insert(80, this->mFont);
            
            break;
        case sf::Keyboard::R: // Reset the AVL tree
            this->tree->resetHelper(this->tree->root);
            break;
        case sf::Keyboard::Escape: // Close the window
            window.close();
            break;
        default:
            break;
        }
    }
};
