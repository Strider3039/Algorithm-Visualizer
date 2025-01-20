#pragma once
#include "TreeWindow.hpp"
#include <SFML/Graphics/Font.hpp>

template <class T>
class GraphicAVL : public GraphicTree<T>
{
public:
    GraphicAVL(float wWidth, float wHeight, sf::Font& font)
        : GraphicTree<T>(wWidth, wHeight),  mFont(font) {}

    void insert(T data, sf::Font& font)
    {
        insert(data, this->root, this->windowWidth / 2, 170, this->windowWidth / 4, font);
    }

    void remove(T data)
    {
        remove(data, this->root);
    }

private:
    sf::Font mFont;  // Storing a copy of the font instead of a reference

    static const int ALLOWED_IMBALANCE = 1;

    void insert(T data, typename GraphicTree<T>::TreeNode*& pNode, float xPos, float yPos, float offset, sf::Font& font) override
    {
        if (pNode == nullptr)
        {
            pNode = new typename GraphicTree<T>::TreeNode(data, font, xPos, yPos);
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

        balance(pNode);
    }

    void remove(T data, typename GraphicTree<T>::TreeNode*& pNode) override
    {
        if (pNode == nullptr)
        {
            return;
        }

        if (data < pNode->data)
        {
            remove(data, pNode->pLeft);
        }
        else if (data > pNode->data)
        {
            remove(data, pNode->pRight);
        }
        else
        {
            if (pNode->pLeft != nullptr && pNode->pRight != nullptr)
            {
                typename GraphicTree<T>::TreeNode* successor = findMin(pNode->pRight);
                pNode->data = successor->data;
                pNode->text.setString(std::to_string(successor->data));
                remove(successor->data, pNode->pRight);
            }
            else
            {
                typename GraphicTree<T>::TreeNode* oldNode = pNode;
                pNode = (pNode->pLeft != nullptr) ? pNode->pLeft : pNode->pRight;
                delete oldNode;
            }
        }

        if (pNode != nullptr)
        {
            balance(pNode);
        }
    }

    void balance(typename GraphicTree<T>::TreeNode*& pNode)
    {
        if (pNode == nullptr)
        {
            return;
        }


        if (this->treeHeight(pNode->pLeft) - this->treeHeight(pNode->pRight) > ALLOWED_IMBALANCE)
        {
            if (this->treeHeight(pNode->pLeft->pLeft) >= this->treeHeight(pNode->pLeft->pRight))
            {
                rotateWithLeftChild(pNode);
            }
            else
            {
                doubleWithLeftChild(pNode);
            }
        }
        else if (this->treeHeight(pNode->pRight) - this->treeHeight(pNode->pLeft) > ALLOWED_IMBALANCE)
        {
            if (this->treeHeight(pNode->pRight->pRight) >= this->treeHeight(pNode->pRight->pLeft))
            {
                rotateWithRightChild(pNode);
            }
            else
            {
                doubleWithRightChild(pNode);
            }
        }
    }

    void rotateWithLeftChild(typename GraphicTree<T>::TreeNode*& k2)
    {
        typename GraphicTree<T>::TreeNode* k1 = k2->pLeft;
        k2->pLeft = k1->pRight;
        k1->pRight = k2;
        k2 = k1;

        GraphicTree<T>::updateNodePositions(this->root, this->windowWidth / 2, 170, this->windowWidth / 4); // Fix layout after balancing
    }

    void rotateWithRightChild(typename GraphicTree<T>::TreeNode*& k2)
    {
        typename GraphicTree<T>::TreeNode* k1 = k2->pRight;
        k2->pRight = k1->pLeft;
        k1->pLeft = k2;
        k2 = k1;

        GraphicTree<T>::updateNodePositions(this->root, this->windowWidth / 2, 170, this->windowWidth / 4); // Fix layout after balancing

    }

    void doubleWithLeftChild(typename GraphicTree<T>::TreeNode*& k3)
    {
        rotateWithRightChild(k3->pLeft);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(typename GraphicTree<T>::TreeNode*& k3)
    {
        rotateWithLeftChild(k3->pRight);
        rotateWithRightChild(k3);
    }

    typename GraphicTree<T>::TreeNode* findMin(typename GraphicTree<T>::TreeNode* pNode)
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

    
};
