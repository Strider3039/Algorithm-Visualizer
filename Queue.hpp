// implementation of queue template class using linkedList members and methods
#include "linkedList.hpp"

template <typename T>
class Queue : public LinkedList<T>
{
public:
Queue();
~Queue()
{

}


// void insert(T elementToInsert) override
// {
//     node* newNode = new node{elementToInsert, nullptr};
//     pBack->pNext = newNode;
//     pBack = newNode; 
// }

// T remove() override
// {
//     if (pFront == nullptr)
//     {
//         return false;
//     }
//     else
//     {
//         node* pTemp = pFront;
//         pFront = pFront->pNext;
//         return pTemp->element;
//     }
// }
    

private:
    
};

/*

|1|-> |2|-> |3|-> |4|
 ^                 ^
pFront             pBack

*/