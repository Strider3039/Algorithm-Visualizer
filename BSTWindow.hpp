#include "GraphicBST.hpp"
#include <SFML/Graphics/Font.hpp>

template <class T>
class BSTWindow : public TreeWindow<T> {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : TreeWindow<T>(width, height, font) {

        this->tree = new GraphicBST<T>(width, height, &this->mFont);

        if (!this->mFont.getInfo().family.empty()) {
        std::cout << "[INFO] BSTWindow received valid font: " << this->mFont.getInfo().family << std::endl;
        } else {
        std::cerr << "[ERROR] BSTWindow received an invalid font!" << std::endl;
        }
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
