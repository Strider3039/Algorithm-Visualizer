// implementation of queue template class using linkedList members and methods
#include "linkedList.hpp"

template <typename T>
class Queue : public LinkedList<T>
{
public:

    void enqueue(T elementToEnqueue)
    {
        this->insertBack(elementToEnqueue);
    }

    T dequeue()
    {
        return this->removeFront();
    }

    bool contains(T elementToFind)
    {
        return this->search(elementToFind);
    }
    
private:
    
};
