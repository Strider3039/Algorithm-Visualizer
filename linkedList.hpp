// implementation of template class linked list
#ifndef LINKEDLIST_HPP 
#define LINKEDLIST_HPP 
#include <iostream>

template <typename T>
class LinkedList
{
public:
    // constructor
    LinkedList() : pFront(nullptr){}

    // destructor
    ~LinkedList()
    {
        removeAll(pFront);
    }

    // inserts at front of list. 
    void insert(T elementToInsert){
        if (pFront == nullptr)
        {
            // list is empty
            node* newNode = new node{elementToInsert, nullptr};

            pFront = newNode;        
            std:: cout << "inserting " << elementToInsert << std::endl;
        }
        else
        {
            // newNode.pNext = pFront.
            node* newNode = new node{elementToInsert, pFront};

            // set pFront to newNode (the new front of the list)
            pFront = newNode;
        }
    } 
    virtual void remove(T elementToRemove){
        //  check for empty list
        if (pFront == nullptr)
        {
            std::cout << "empty" << std::endl;
            return;
        }
        node* pCur = pFront;
        
        //  check edge case: first node in list is target element
        if (pCur->element == elementToRemove)
        {
            pFront = pCur->pNext;
            std::cout << "deleting " << elementToRemove << std::endl;
            return delete pCur;
        }
        //  iterate throug list 
        while (pCur->pNext != nullptr)
        {
            //  element found
            if (pCur->pNext->element == elementToRemove)
            {
                node* pTemp = pCur->pNext;
                pCur = pTemp->pNext;
                std::cout << "deleting " << elementToRemove << std::endl;
                return delete pTemp;
            }
            pCur = pCur->pNext;
        }
        return;
    }

private:

    struct node
    {
        T element; 
        node* pNext;  

        node(const T & theElement, node* next) : element(theElement), pNext(next) {}
        node(T & theElement, node* next) : element(theElement), pNext(next) {}
    }; 

    node* pFront; 

    virtual void removeAll(node*& pCur){
        if (pCur == nullptr)
        {
            return;
        }
        removeAll(pCur->pNext);
        delete pCur;
    }

    bool search(T targetElement)
    {
        node* pCur = pFront;
        while (pCur != nullptr)
        {
            if (pCur->element == targetElement)
            {
                return true;
            }
        }
        return false;
    }

    bool isEmpty()
    {
        return pFront == nullptr;
    }
};
#endif