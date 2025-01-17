#include "GraphicBST.hpp"

template <class T>
class GraphicAVL : public GraphicBST<T>
{
public:

    inline void insert(T insertData)
    {
        insert(insertData, this->root);
    }

    inline void remove(T removeData)
    {
        remove(removeData, this->root);
    }

    inline bool isBalanced()
    {
        return isBalanced(this->root);
    }

    static const int ALLOWED_IMBALANCE = 1;

private:

    inline void insert(T insertData, typename GraphicBST<T>::treeNode*& pNode)
    {
        GraphicBST<T>::insert(insertData, pNode);
        balance(pNode);
    }

    inline void remove(T removeData, typename GraphicBST<T>::treeNode*& pNode)
    {
        GraphicBST<T>::remove(removeData, pNode);
        balance(pNode);
    }

    void balance(typename GraphicBST<T>::treeNode*& pNode)
    {
        if( pNode == nullptr ) {
            return;
        }

        if( this->treeHeight( pNode->pLeft ) - this->treeHeight( pNode->pRight ) > ALLOWED_IMBALANCE ) {
            if( this->treeHeight( pNode->pLeft->pLeft ) >= this->treeHeight( pNode->pLeft->pRight ) ) {
                rotateWithLeftChild( pNode);
            }
            else {
                doubleWithLeftChild( pNode );
            }
        }
        else if( this->treeHeight( pNode->pRight ) - this->treeHeight( pNode->pLeft ) > ALLOWED_IMBALANCE ) {
            if( this->treeHeight( pNode->pRight->pRight ) >= this->treeHeight( pNode->pRight->pLeft ) ) {
                rotateWithRightChild( pNode );
            }
            else {
                doubleWithRightChild( pNode );
            }
        }
    }

    void rotateWithLeftChild(typename GraphicBST<T>::treeNode*& k2)
    {
    /*
    Case 1:
    
           k2
          /  
        k1    
       /
     T0

    */

        typename GraphicBST<T>::treeNode* k1 = k2->pLeft;
        k2->pLeft = k1->pRight;
        k1->pRight = k2;
        k2 = k1;
    }

    void rotateWithRightChild(typename GraphicBST<T>::treeNode*& k2)
    {

    /*
    Case 2:

     k2
       \
        k1
          \
           T0
    
    */

        typename GraphicBST<T>::treeNode* k1 = k2->pRight;
        k2->pRight = k1->pLeft;
        k1->pLeft = k2;
        k2 = k1;
        
    }

    void doubleWithLeftChild(typename GraphicBST<T>::treeNode*& k3)
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

    void doubleWithRightChild(typename GraphicBST<T>::treeNode*& k3)
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

    bool isBalanced(typename GraphicBST<T>::treeNode* pNode)
    {
        if (abs(this->treeHeight(this->root->pLeft) - this->treeHeight(this->root->pRight)) <= ALLOWED_IMBALANCE) 
        {
            return true;
        }

        return false;
    }
    
};