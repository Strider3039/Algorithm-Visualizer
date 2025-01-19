#include "GraphicBST.hpp"



template <class T>
class BSTWindow : public TreeWindow<T> {
public:
    BSTWindow(float width, float height, sf::Font& font)
        : TreeWindow<T>(width, height, font) {
        this->tree = new GraphicBST<T>(width, height);
    }

    ~BSTWindow() {
        delete this->tree;
    }

protected:
    void initializeTree() override {}

    void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) override {
        if (key == sf::Keyboard::R) {
            this->tree->reset();
        }
    }
};
