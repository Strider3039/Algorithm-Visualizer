#include "Header.hpp"

    

template <class T>
class BST 
{
public:


    BST() : root(nullptr) {};

    inline T findMin() {
        if (root == NULL) {
            throw std::underflow_error("Tree is empty");
        }

        return findMin(root)->element;
    }

    inline T findMax(){

        if (root == NULL) {
            throw std::underflow_error("Tree is empty");
        }

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

    inline int treeHeight() {
        return treeHeight(root);
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

protected:

    struct treeNode 
    {
        T element;
        treeNode* pLeft;
        treeNode* pRight;
        
        treeNode(const T& element, treeNode* pLeft, treeNode* pRight) : element(element), pLeft(pLeft), pRight(pRight) {};

        treeNode(const T&& element, treeNode* pLeft, treeNode* pRight) : element(std::move(element)), pLeft(pLeft), pRight(pRight) {};


    };

    treeNode* root;
    typename BST<T>::treeNode* findMin(treeNode* pNode);
    typename BST<T>::treeNode* findMax(treeNode* pNode);
    void insert(T insertData, treeNode*& pNode);
    void remove(T removeData, treeNode*& pNode);
    bool contains(T data, treeNode* pNode);
    bool isEmpty(treeNode* pNode);
    int treeSize(treeNode* pNode);
    int treeHeight(treeNode* pNode);
    void printInOrder(treeNode* pNode);
    void printPostOrder(treeNode* pNode);
    void printPreOrder(treeNode* pNode);


};

template <class T>
typename BST<T>::treeNode* BST<T>::findMin(treeNode* pNode)
{
    if (pNode == nullptr) return nullptr;
    
    if (pNode->pLeft == nullptr) return pNode;

    return findMin(pNode->pLeft);

}

template <class T>
typename BST<T>::treeNode* BST<T>::findMax(treeNode* pNode)
{
    if (pNode == nullptr) return nullptr;

    if (pNode->pRight == nullptr) return pNode;

    return findMax(pNode->pRight);
}

template <class T>
void BST<T>::insert(T insertData, treeNode*& pNode)
{
    if (pNode == nullptr) 
    {
        pNode = new treeNode(insertData, nullptr, nullptr);
    }

    if (insertData < pNode->element) 
    {
        insert(insertData, pNode->pLeft);
    }
    else if (insertData > pNode->element)
    {
        insert(insertData, pNode->pRight);
    }

}

template <class T>
void BST<T>::remove(T removeData, treeNode*& pNode)
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
            
            pNode->element = findMin(pNode->pRight)->element;
            remove(pNode->element, pNode->pRight);
        }
        else // one child
        {
            treeNode* deleteNode = pNode;

            pNode = (pNode->pRight == nullptr) ? pNode->pLeft : pNode->pRight;
            delete deleteNode;

        }
        

    }
}

template <class T>
bool BST<T>::contains(T data, treeNode* pNode)
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
bool BST<T>::isEmpty(treeNode* pNode)
{
    return (pNode == nullptr);
}

template <class T>
int BST<T>::treeSize(treeNode* pNode)
{
    if (isEmpty(pNode)) return 0;

    int size = treeSize(pNode->pLeft) + treeSize(pNode->pRight);

    return 1 + size;

}

template <class T>
int BST<T>::treeHeight(treeNode* pNode)
{
    if (isEmpty(pNode)) return -1;

    int maxHeight = std::max(treeHeight(pNode->pLeft), treeHeight(pNode->pRight));

    return 1 + maxHeight;
}


template <class T>
void BST<T>::printInOrder(treeNode* pNode)
{
    if (pNode == nullptr) return;

    printInOrder(pNode->pLeft);
    cout << pNode->element << " ";
    printInOrder(pNode->pRight);
}

template <class T>
void BST<T>::printPreOrder(treeNode* pNode)
{
    if (pNode == nullptr) return;

    cout << pNode->element << " ";
    printInOrder(pNode->pLeft);
    printInOrder(pNode->pRight);
}

template <class T>
void BST<T>::printPostOrder(treeNode* pNode)
{
    if (pNode == nullptr) return;

    printInOrder(pNode->pLeft);
    printInOrder(pNode->pRight);
    cout << pNode->element << " ";
}

