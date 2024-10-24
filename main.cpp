#include "Avl.hpp"
#include "Stack.hpp"
#include <SFML/Graphics.hpp>

int main(void)
{
    Queue<int> queueOBJ;

    queueOBJ.enqueue(5);

    std::cout << queueOBJ.isEmpty() << std::endl;

    std::cout << queueOBJ.contains(5) << std::endl;

    std::cout << queueOBJ.contains(7) << std::endl;

    std::cout << queueOBJ.dequeue() << std::endl;

    return 0;
}
