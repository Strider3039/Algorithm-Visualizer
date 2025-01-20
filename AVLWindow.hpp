#pragma once

#include "GraphicAvl.hpp"
#include "TreeWindow.hpp"


template <class T>
class AVLWindow : public TreeWindow<T>
{
public:
    AVLWindow(float width, float height, sf::Font& font)
        : TreeWindow<T>(width, height, font)
    {
        this->tree = new GraphicAVL<T>(width, height, font);
    }

    ~AVLWindow()
    {
        delete this->tree;
    }

protected:
    void initializeTree() override
    {
        // Any specific initialization if required
    }

    void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) override
    {
        switch (key)
        {
        case sf::Keyboard::Num1: // Insert test values
            this->tree->insert(20, this->mFont);
            this->tree->insert(50, this->mFont);
            this->tree->insert(30, this->mFont);
            this->tree->insert(70, this->mFont);
            this->tree->insert(40, this->mFont);
            this->tree->insert(60, this->mFont);
            this->tree->insert(80, this->mFont);
            this->tree->insert(10, this->mFont);
            this->tree->insert(5, this->mFont);
            this->tree->insert(15, this->mFont);
            this->tree->insert(25, this->mFont);
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
