#include "Header.hpp"

    

template <class T>
class BST 
{
public:


    BST() : root(nullptr) {};

    inline T findMin() {
        return findMin(root)->element;
    }

    inline T findMax(){
        return findMax(root)->element;
    }

    inline void insert(T insertData) {
        insert(insertData, root);
    }

    inline void remove(T removeData) {
        remove(removeData, root);
    }

    inline bool contains(T data) {
        return contains(data, root);
    }

    inline bool isEmpty() {
        return (root == nullptr) ? true : false;
    }

    inline int treeSize() {
        return treeSize(root);
    }

    inline void printInOrder() {
        printInOrder(root);
    }

    inline void printPostOrder() {
        printPostOrder(root);
    }
    inline void printPreOrder() {
        printPreOrder(root);
    }

private:

    struct BSTNode 
    {
        T element;
        BSTNode* pLeft;
        BSTNode* pRight;
        
        BSTNode(const T& element, BSTNode* left, BSTNode* right) : element(element), pLeft(left), pRight(right) {};

        BSTNode(const T&& element, BSTNode* left, BSTNode* right) : element(std::move(element)), pLeft(left), pRight(right) {};


    };

    BSTNode* root;
    typename BST<T>::BSTNode* findMin(BSTNode* pNode);
    typename BST<T>::BSTNode* findMax(BSTNode* pNode);
    void insert(T insertData, BSTNode*& pNode);
    void remove(T removeData, BSTNode*& pNode);
    bool contains(T data, BSTNode* pNode);
    bool isEmpty(BSTNode* pNode);
    
    void printInOrder(BSTNode* pNode);
    void printPostOrder(BSTNode* pNode);
    void printPreOrder(BSTNode* pNode);


};

template <class T>
typename BST<T>::BSTNode* BST<T>::findMin(BSTNode* pNode)
{
    if (pNode == nullptr) return nullptr;
    
    if (pNode->pLeft == nullptr) return pNode;

    return findMin(pNode->pLeft);

}

template <class T>
typename BST<T>::BSTNode* BST<T>::findMax(BSTNode* pNode)
{
    if (pNode == nullptr) return nullptr;

    if (pNode->pRight == nullptr) return pNode;

    return findMax(pNode->pRight);
}

template <class T>
void BST<T>::insert(T insertData, BSTNode*& pNode)
{
    if (pNode == nullptr) 
    {
        pNode = new BSTNode(insertData, nullptr, nullptr);
    }

    if (insertData < pNode->element) 
    {
        insert(insertData, pNode->pLeft);
    }
    else 
    {
        insert(insertData, pNode->pRight);
    }

}

template <class T>
void BST<T>::remove(T removeData, BSTNode*& pNode)
{
    if (pNode == nullptr) return;

    else if (removeData < pNode->element)
    {
        remove(removeData, pNode->pLeft);
    }
    else if (removeData > pNode->element)
    {
        remove(removeData, pNode->pRight);
    }
    else {
        // node found

        if (pNode->pLeft != nullptr && pNode->pRight != nullptr) // two children
        {
            
            pNode->element = findMin(pNode->pRight);
            remove(pNode->element, pNode->pRight);
        }
        else 
        {
            BSTNode* deleteNode = pNode;

            pNode = (pNode->right == nullptr) ? pNode->pLeft : pNode->pRight;
            delete deleteNode;

        }
        

    }
}

template <class T>
bool BST<T>::contains(T data, BSTNode* pNode)
{
    if (pNode == nullptr) return false;

    if (data < pNode->element)
    {
        return contains(data, pNode->pLeft);
    }
    else if (data > pNode->element)
    {
        return contains(data, pNode->pRight);
    }

    return true;
}

template <class T>
bool BST<T>::isEmpty(BSTNode* pNode)
{
    return (root == nullptr);
}


template <class T>
void BST<T>::printInOrder(BSTNode* pNode)
{
    if (isEmpty()) return;

    printInOrder(pNode->pLeft);
    cout << pNode->element << " ";
    printInOrder(pNode->pRight);
}

template <class T>
void BST<T>::printPreOrder(BSTNode* pNode)
{
    if (isEmpty()) return;

    cout << pNode->element << " ";
    printInOrder(pNode->pLeft);
    printInOrder(pNode->pRight);
}

template <class T>
void BST<T>::printPostOrder(BSTNode* pNode)
{
    if (isEmpty()) return;

    printInOrder(pNode->pLeft);
    printInOrder(pNode->pRight);
    cout << pNode->element << " ";
}

