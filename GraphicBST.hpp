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


    GraphicBST() : root(nullptr), windowWidth(800), windowHeight(600) {}

    GraphicBST(float wWidth, float wHeight) : root(nullptr), windowWidth(wWidth), windowHeight(wHeight) {}

    void insert(T data, sf::Font& font)
    {
        insert(data, root, windowWidth / 2, 170,  windowHeight / 2, font);
    }

    void remove(T data) 
    {
        remove(data, root);
    }


    void draw(sf::RenderWindow& window)
    {
        draw(window, root);
    }

    // Function to reset the tree
    void reset()
    {
        resetHelper(root);
    }

protected:

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
            insert(data, pNode->pLeft, xPos - offset, yPos + 150, offset / 2, font);
        }
        else if (data > pNode->data)
        {
            insert(data, pNode->pRight, xPos + offset, yPos + 150, offset / 2, font);
        }
    }


    void remove(T data, TreeNode*& pNode)
    {
        if (pNode == nullptr)
        {
            return; // Node not found
        }

        if (data < pNode->data)
        {
            remove(data, pNode->pLeft); // Search left subtree
        }
        else if (data > pNode->data)
        {
            remove(data, pNode->pRight); // Search right subtree
        }
        else
        {
            // Node found
            if (pNode->pLeft != nullptr && pNode->pRight != nullptr)
            {
                // Case: Two children
                TreeNode* successor = findMin(pNode->pRight);
                pNode->data = successor->data; // Replace with successor data
                pNode->text.setString(std::to_string(successor->data)); // Update the displayed text
                remove(successor->data, pNode->pRight); // Remove the successor
            }
            else
            {
                // Case: One or no child
                TreeNode* oldNode = pNode;
                pNode = (pNode->pLeft != nullptr) ? pNode->pLeft : pNode->pRight;
                if (pNode != nullptr)
                {
                    // Update graphical position of the replacement node
                    pNode->position = oldNode->position;
                    pNode->shape.setPosition(oldNode->position);
                    auto bounds = pNode->text.getLocalBounds();
                    pNode->text.setPosition(oldNode->position.x + pNode->shape.getRadius() - bounds.width / 2,
                    oldNode->position.y + pNode->shape.getRadius() - bounds.height);
                }
                delete oldNode; // Free memory
            }
        }
    }


    TreeNode* findMin(TreeNode* pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }
        else if (pNode->pLeft == nullptr)
        {
            return pNode;
        }
        else 
        {
            return findMin(pNode->pLeft);
        }
    }

    int treeHeight(TreeNode* pNode)
{
    if (pNode == nullptr)
    {
        return -1; // Base case: Height of an empty tree is -1
    }

    // Recursively calculate the height of the left and right subtrees
    int leftHeight = treeHeight(pNode->pLeft);
    int rightHeight = treeHeight(pNode->pRight);

    // Return the maximum height of the two subtrees plus one for the current node
    return std::max(leftHeight, rightHeight) + 1;
}


    void resetHelper(TreeNode*& pNode)
    {
        if (pNode == nullptr)
        {
            return;
        }

        resetHelper(pNode->pLeft);
        resetHelper(pNode->pRight);

        delete pNode;
        pNode = nullptr;
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
            sf::Vertex(parentPos + sf::Vector2f(20, 20), sf::Color::Black),
            sf::Vertex(childPos + sf::Vector2f(20, 20), sf::Color::Black)
        };

        window.draw(line, 2, sf::Lines);
    }


};