#include "GraphicBST.hpp"
#include <SFML/Graphics/Font.hpp>

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
        if (key == sf::Keyboard::R) 
        {
            this->tree->resetHelper(this->tree->root);
        }
    }
};
