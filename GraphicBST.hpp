#pragma once

#include "TreeWindow.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <X11/X.h>

template <class T>
class GraphicBST : public GraphicTree<T>
{
public:
    GraphicBST(float wWidth, float wHeight, sf::Font& font)
    : GraphicTree<T>(wWidth, wHeight), mFont(font)
    {
        root = nullptr;

    }

    void remove(T data)
    {
        GraphicTree<T>::remove(data, this->root);
    }

    void reset()
    {
        GraphicTree<T>::resetHelper(this->root);
    }

protected:
    float windowWidth;
    float windowHeight;
    sf::Font mFont;  // Storing a copy of the font instead of a reference
    typename GraphicTree<T>::TreeNode* root;

};
