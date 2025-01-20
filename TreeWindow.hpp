#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <vector>
#include "menuItems.hpp"

// trying a completely new design for the trees. Stuff is not working properly
// line 275 is TreeWindow base class

template <class T>
class GraphicTree {
public:

    GraphicTree(float width, float height)
        : windowWidth(width), windowHeight(height)
    {
        root = nullptr;
    }


    virtual ~GraphicTree() 
    {
        resetHelper(root);
        //updateNodePositions(root, windowWidth / 2, 170, windowWidth / 4);
    }

    void insert(T data, sf::Font& mFont)
    {
        insert(data, root, windowWidth / 2, 170, windowWidth / 4, mFont);
        //updateNodePositions(root, windowWidth / 2, 170, windowWidth / 4);

    }

    void draw(sf::RenderWindow& window)
    {
        draw(window, root);
    }

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
    float windowWidth;
    float windowHeight;

    void printNodeData(TreeNode* pNode)
    {
        if (pNode == nullptr) return;

        printNodeData(pNode->pLeft);
        cout << pNode->data << " " << pNode->position.x << " " << pNode->position.y << " " << pNode->text.getString().toAnsiString() << endl ;
        printNodeData(pNode->pRight);
    }

    virtual void insert(T data, TreeNode*& pNode, float xPos, float yPos, float offset, sf::Font& font)
    {
        if (pNode == nullptr)
        {
            pNode = new TreeNode(data, font, xPos, yPos);
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


    virtual void remove(T data, TreeNode*& pNode)
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

    virtual void resetHelper(TreeNode*& pNode)
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

    void updateNodePositions(typename GraphicTree<T>::TreeNode* pNode, float xPos, float yPos, float offset)
    {
        if (pNode == nullptr) return;

        pNode->position = {xPos, yPos};
        pNode->shape.setPosition(xPos, yPos);
        auto bounds = pNode->text.getLocalBounds();
        pNode->text.setPosition(xPos + pNode->shape.getRadius() - bounds.width / 2, yPos + pNode->shape.getRadius() - bounds.height);

        if (pNode->pLeft != nullptr)
        {
            this->updateNodePositions(pNode->pLeft, xPos - offset, yPos + 150, offset / 2);
        }
        if (pNode->pRight != nullptr)
        {
            this->updateNodePositions(pNode->pRight, xPos + offset, yPos + 150, offset / 2);
        }
    }

    virtual void draw(sf::RenderWindow& window, TreeNode* pNode)
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

        if (pNode != nullptr)
        {
            window.draw(pNode->shape);
            window.draw(pNode->text);
        }

        
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


// ===========================================================================================================================
// ===========================================================================================================================


template <class T>
class TreeWindow {
public:
    TreeWindow(float width, float height, sf::Font& font)
        : windowWidth(width), windowHeight(height), mFont(font), isRunning(true) 
    {
        loadColors(colors);

    }

    void runVisual(sf::RenderWindow& window) 
    {
        loadButtonUI(UI, mFont, windowWidth, windowHeight, colors);

        while (window.isOpen()) 
        {
            processEvents(window);
            render(window);

            if (!isRunning) 
            {
                isRunning = true;
                return;
            }
        }
    }

protected:
    double windowWidth;
    double windowHeight;
    sf::Font mFont;  // Copying the font instead of referencing
    sf::Text text;
    sf::RectangleShape background;
    sf::Color backgroundColor;
    bool isRunning;
    std::vector<std::pair<Button, TextBox>> UI;
    sf::Event emptyEvent;
    Colors colors;

    // Polymorphic Graphic Tree Pointer
    GraphicTree<T>* tree;

    virtual void initializeTree() = 0; // To be implemented by derived classes

    void processEvents(sf::RenderWindow& window) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::KeyPressed) 
            {
                handleKeyPress(event.key.code, window);
            }

            if (UI[0].first.scrollAndClick(event, window)) 
            {
                isRunning = false;
            }

            for (auto& UI_Element : UI) 
            {
                handleTextInput(window, event, UI_Element);
                handleButtons(window, event, UI_Element);
            }
        }
    }

    void handleTextInput(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& UI_Element) 
    {
        if (UI_Element.second.scrollAndClick(event, window)) 
        {
            resetEvent(event);
            while (event.type != sf::Event::MouseButtonPressed) 
            {
                if (window.pollEvent(event) && event.type == sf::Event::TextEntered) 
                {
                    if (event.text.unicode == 27 /* Escape */ || event.text.unicode == 13 /* Enter */)
                        break;

                    UI_Element.second.write(event.text.unicode, window);





                    resetEvent(event);
                }
                render(window);
            }
        }
    }

    void resetEvent(sf::Event& event) 
    {
        event = emptyEvent;
    }

    void handleButtons(sf::RenderWindow& window, sf::Event& event, std::pair<Button, TextBox>& UI_Element) 
    {
        std::string buttonStr = UI_Element.first._getStr();
        std::string inputStr = UI_Element.second._getText();

        if (UI_Element.first.scrollAndClick(event, window)) 
        {
            if (!inputStr.empty() && std::all_of(inputStr.begin(), inputStr.end(), ::isdigit)) 
            {
                if (buttonStr == "Insert") 
                {
                    tree->insert(std::stoi(inputStr), mFont);
                }

                if (buttonStr == "Remove") 
                {
                    tree->remove(std::stoi(inputStr), tree->root);
                }
            }
        }
    }

    virtual void handleKeyPress(sf::Keyboard::Key key, sf::RenderWindow& window) = 0;

    virtual void render(sf::RenderWindow& window) 
    {
        window.clear(colors.backgroundElementsColor);

        tree->draw(window);
        
        drawUI(window);
        window.display();
    }

    void drawUI(sf::RenderWindow& window) 
    {
        for (auto& UI_Element : UI) 
        {
            window.draw(UI_Element.first);
            window.draw(UI_Element.second);
        }
    }
};
