#pragma once
#include "TreeWindow.hpp"
#include "linkedList.hpp"
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
#include <SFML/Window/WindowHandle.hpp>
#include <X11/X.h>
#include <atomic>
#include <cstddef>
#include <string>


template <class T>
class GraphicBST : GraphicTree<T>
{
public:

    GraphicBST(float wWidth, float wHeight, sf::Font& font) 
    {
        this->windowWidth = wWidth;
        this->windowHeight = wHeight;
        this->mFont = font;
    }

    void insert(T data)
    {
        GraphicTree<T>::insert(data, this->root, this->root->position.x)
    }


protected:



};