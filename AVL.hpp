#include "BST.hpp"

template <class T>
class AVL : public BST<T>
{
public:

    void insert(T insertData)
    {
        insertData(insertData, this->root);
    }

    void remove(T removeData)
    {
        remove(removeData, this->root);
    }

private:

    void insert(T insertData, typename BST<T>::BSTNode* pNode)
    {
        BST<T>::insert(insertData, pNode);
        // balance(pNode)
    }

    void remove(T removeData, typename BST<T>::BSTNode* pNode)
    {
        BST<T>::remove(removeData, pNode);
        // balance(pNode)
    }

    

};