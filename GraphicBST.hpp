#pragma once
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
#include "nodeGraphic.hpp"
#include "Button.hpp"
#include "menuItems.hpp"
#include "textBox.hpp"


template <class T>
class GraphicBST
{
public:

    /*
        Functions:

        Constructor (root, window width, window height) {}

        Insert (data, &font)
            Call private insert 

        Draw (&window)
            call private draw
    */


    GraphicBST() : root(nullptr), windowWidth(800), windowHeight(600) {}

    GraphicBST(float wWidth, float wHeight) : root(nullptr), windowWidth(wWidth), windowHeight(wHeight) {}

    void insert(T data, sf::Font& font)
    {
        insert(data, root, windowWidth / 2, 200,  windowHeight / 2, font);
    }

    void draw(sf::RenderWindow& window)
    {
        draw(window, root);
    }

    // Function to reset the tree
    void reset()
    {
        root = nullptr;
    }

private:

    /*
        DATA

        struct TreeNode {
            left and right nodes
            shape, text, position

            Constructor (T data, &font, xPos, yPos) : data(data), pLeft(nullptr), pRight(nullptr) {
            
                NODE VISUAL INFORMATION
                setRadius
                setFillColor
                setOutlineColor
                setOutlineThickness
                position = {xPos, yPos};
                setPosition

                LABEL VISUAL INFORMATION
                setfont
                setString
                setCharacterSize
                setFillColor
                getLocalBounds
                setPosition (make sure to center properly)


            
            }
        };

        TreeNode* root
        float windowWidth, windowHeight


        FUNCTIONS

        Insert (data, *&node, x, y, offset, &font)  (offset for centering nodes as the tree gets deeper)
            if nodePtr is null
                create new treeNode and put data inside it
            
            if data is less than current node value
                recurse insert with x - offset, offset / 2
            if data is more that current node value
                recurse insert with x + offset, offset / 2

        Draw (&window, *node)
            if node is null return
           
            if node->pLeft isn't null
                draw node->pLeft
                draw node->pLeft edge
            if node->pRight isnt null
                draw node->pRight
                draw node->pRight edge
            
            (drawEdge function call for each)


        Draw Edge (&window, parentPos, childPos)
            use sf::Vertex to create a line from parentPos to childPos

            call draw function to draw line at end
    */

    struct TreeNode
    {
        T data;
        TreeNode* pLeft;
        TreeNode* pRight;
        sf::CircleShape shape;
        sf::Text text;
        sf::Vector2f position;

        TreeNode(T data, sf::Font& font, float xPos, float yPos)
        : data(data), pLeft(nullptr), pRight(nullptr)
        {
            // node visuals
            shape.setRadius(20);
            shape.setFillColor(sf::Color::Black);
            shape.setOutlineColor(sf::Color::White);
            shape.setOutlineThickness(5);
            position = {xPos, yPos};
            shape.setPosition(xPos, yPos);

            // text visuals
            text.setFont(font);
            text.setString(std::to_string(data));
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::White);
            auto bounds = text.getLocalBounds();
            text.setPosition(xPos + shape.getRadius() - bounds.width / 2, yPos + shape.getRadius() - bounds.height);
        }

    };

    TreeNode* root;
    float windowWidth, windowHeight;

    void insert(T data, TreeNode*& pNode, float xPos, float yPos, float offset, sf::Font& font)
    {
        if (pNode == nullptr)
        {
            pNode = new TreeNode(data, font, xPos, yPos);  // Link the new node
            return;
        }

        if (data < pNode->data)
        {
            insert(data, pNode->pLeft, xPos - offset, yPos + 75, offset / 2, font);
        }
        else if (data > pNode->data)
        {
            insert(data, pNode->pRight, xPos + offset, yPos + 75, offset / 2, font);
        }
    }

    void draw(sf::RenderWindow& window, TreeNode* pNode)
    {
        if (pNode == nullptr) return;

        if (pNode->pLeft != nullptr)
        {
            drawEdge(window, pNode->position, pNode->pLeft->position);
            draw(window, pNode->pLeft);
        }
        if (pNode->pRight != nullptr)
        {
            drawEdge(window, pNode->position, pNode->pRight->position);
            draw(window, pNode->pRight);
        }

        window.draw(pNode->shape);
        window.draw(pNode->text);
    }

    void drawEdge(sf::RenderWindow& window, sf::Vector2f parentPos, sf::Vector2f childPos)
    {
        sf::Vertex line[] = {
            sf::Vertex(parentPos + sf::Vector2f(20, 20), sf::Color::White),
            sf::Vertex(childPos + sf::Vector2f(20, 20), sf::Color::White)
        };

        window.draw(line, 2, sf::Lines);
    }


};