# include "Queue.hpp"

// implementation of stack template class using linkedList members and methods
#include "linkedList.hpp"

template <typename T>
class Stack : public LinkedList<T>
{
public:

    void push(T elementToPush)
    {
        this->insertFront(elementToPush);
    }

    T pop()
    {
        T top = peek();
        this->removeSelected(this->pFront->element);
        return top;
    }

    T peek()
    {
        return this->pFront->element;
    }
    
    bool contains(T elementToFind)
    {
        return this->search(elementToFind);
    }

private:
    
};