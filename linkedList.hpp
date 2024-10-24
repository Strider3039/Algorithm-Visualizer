// implementation of template class linked list
#ifndef LINKEDLIST_HPP 
#define LINKEDLIST_HPP 
#include "Header.hpp"

template <typename T>
class LinkedList
{
public:
    LinkedList() : pFront(nullptr), pBack(nullptr){}
    ~LinkedList()
    {
        removeAll(pFront);
    }

    // insert at front
    void insertFront(T elementToInsert){
        if (pFront == nullptr)  // list is empty
        {
            node* newNode = new node{elementToInsert, nullptr};

            pFront = newNode;   
            pBack = newNode;
                
            std:: cout << "inserting " << elementToInsert << std::endl;
        }
        else
        {
            node* newNode = new node{elementToInsert, pFront};
            pFront = newNode;
        }
    } 

    // insert at back -- for queue implementation
    void insertBack(T elementToInsert){
        if (pBack == nullptr)  // list is empty
        {
            node* newNode = new node{elementToInsert, nullptr};

            pFront = newNode;   
            pBack = newNode;
                    
            std:: cout << "inserting " << elementToInsert << std::endl;
        }
        else
        {
            node* newNode = new node{elementToInsert, nullptr};
            pBack->pNext = newNode;
            pBack = newNode;
        }
    } 

    // remove selected
    void removeSelected(T elementToRemove) {
        if (pFront == nullptr)
        {
            std::cout << "empty" << std::endl;
            return;
        }

        node* pCur = pFront;
        
        if (pCur->element == elementToRemove)
        {
            pFront = pCur->pNext;
            std::cout << "deleting " << elementToRemove << std::endl;
            return delete pCur;
        }
        while (pCur->pNext != nullptr)
        {
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

    bool isEmpty()
    {
        return pFront == nullptr;
    }

protected:

    struct node
    {
        T element; 
        node* pNext;  

        node(const T & theElement, node* next) : element(theElement), pNext(next) {}
        node(T & theElement, node* next) : element(theElement), pNext(next) {}
    }; 

    node* pFront; 
    node* pBack;

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
            pCur = pCur->pNext;
        }
        return false;
    }

    // remove from front -- used for queue implementation
    T removeFront()
    {
        if (pFront == nullptr)
        {
            std::cout << "list empty" << std::endl;
            return T();
        }
        T temp = pFront->element;
        node* pTemp = pFront;
        pFront = pFront->pNext;
        delete pTemp;
        return temp;
    }
 
};
#endif