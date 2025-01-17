#pragma once
#include "GraphicBST.hpp"
#include <SFML/Graphics/Rect.hpp>

template <class T>
class GraphicAVL : public GraphicBST<T>
{
public:

    GraphicAVL(float wWidth, float wHeight) : windowWidth(wWidth), windowHeight(wHeight) {};


    inline void insert(T data, sf::Font font)
    {
        insert(data, this->root, this->windowWidth / 2, 170, this->windowHeight / 2, font);
    }

    inline void remove(T data)
    {
        remove(data, this->root);
    }

    inline bool isBalanced()
    {
        return isBalanced(this->root);
    }

    static const int ALLOWED_IMBALANCE = 1;

private:

    float windowWidth, windowHeight;

    void insert(T data, typename GraphicBST<T>::TreeNode*& pNode, float xPos, float yPos, float offset, sf::Font& font)
    {
        GraphicBST<T>::insert(data, pNode, xPos, yPos, offset, font);
        balance(pNode);
    }

    inline void remove(T data, typename GraphicBST<T>::TreeNode*& pNode)
    {
        GraphicBST<T>::remove(data, pNode);
        balance(pNode);
    }

    void balance(typename GraphicBST<T>::TreeNode*& pNode)
    {
        if( pNode == nullptr ) {
            return;
        }

        if( this->treeHeight( pNode->pLeft ) - this->treeHeight( pNode->pRight ) > ALLOWED_IMBALANCE ) 
        {
            if ( this->treeHeight( pNode->pLeft->pLeft ) >= this->treeHeight( pNode->pLeft->pRight ) ) 
            {
                rotateWithLeftChild( pNode);
            }
            else 
            {
                doubleWithLeftChild( pNode );
            }
        }
        else if( this->treeHeight( pNode->pRight ) - this->treeHeight( pNode->pLeft ) > ALLOWED_IMBALANCE ) 
        {
            if ( this->treeHeight( pNode->pRight->pRight ) >= this->treeHeight( pNode->pRight->pLeft ) ) 
            {
                rotateWithRightChild( pNode );
            }
            else {
                doubleWithRightChild( pNode );
            }
        }
    }

    void rotateWithLeftChild(typename GraphicBST<T>::TreeNode*& k2)
    {
    /*
    Case 1:
    
           k2
          /  
        k1    
       /
     T0

    */

        typename GraphicBST<T>::TreeNode* k1 = k2->pLeft;
        k2->pLeft = k1->pRight;
        k1->pRight = k2;
        k2 = k1;

        updateGraphics(k1);
        updateGraphics(k2);
    }

    void rotateWithRightChild(typename GraphicBST<T>::TreeNode*& k2)
    {

    /*
    Case 2:

     k2
       \
        k1
          \
           T0
    
    */

        typename GraphicBST<T>::TreeNode* k1 = k2->pRight;
        k2->pRight = k1->pLeft;
        k1->pLeft = k2;
        k2 = k1;

        updateGraphics(k1);
        updateGraphics(k2);
        
    }

    void doubleWithLeftChild(typename GraphicBST<T>::TreeNode*& k3)
    {
    /*
    Case 3:

         K3
        /
      K2
        \
         T0

    */

    rotateWithRightChild(k3->pLeft);
    rotateWithLeftChild(k3);
    } 

    void doubleWithRightChild(typename GraphicBST<T>::TreeNode*& k3)
    {
    /*
    Case 4:

      K3
        \
         K2
        /
      T0
    
    */

    rotateWithLeftChild(k3->pRight);
    rotateWithRightChild(k3);
    }

    void updateGraphics(typename GraphicBST<T>::TreeNode* pNode)
    {
        if (pNode == nullptr)
        {
            return;
        }

        // Update the position of the node's shape and text
        pNode->shape.setPosition(pNode->position);

        sf::FloatRect bounds = pNode->text.getLocalBounds();
        pNode->text.setPosition(
            pNode->position.x + pNode->shape.getRadius() - bounds.width / 2,
            pNode->position.y + pNode->shape.getRadius() - bounds.height
        );

        // Recursively update the graphics of left and right children
        if (pNode->pLeft != nullptr)
        {
            pNode->pLeft->position = {pNode->position.x - 50, pNode->position.y + 50};
            updateGraphics(pNode->pLeft);
        }

        if (pNode->pRight != nullptr)
        {
            pNode->pRight->position = {pNode->position.x + 50, pNode->position.y + 50};
            updateGraphics(pNode->pRight);
        }
    }


    bool isBalanced(typename GraphicBST<T>::TreeNode* pNode)
    {
        if (abs(this->treeHeight(this->root->pLeft) - this->treeHeight(this->root->pRight)) <= ALLOWED_IMBALANCE) 
        {
            return true;
        }

        return false;
    }
    
};