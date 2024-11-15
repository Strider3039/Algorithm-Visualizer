#include "newButton.hpp"
#include <SFML/Graphics/Font.hpp>


inline void mainMenuItems(vector<Button>& buttons, sf::Font& font, double width, double height)
{
    Button list_button("Linked List", font, sf::Vector2f(width / 2, 3*height / 10));
    Button queue_button("Queue", font, sf::Vector2f(width / 2, 4*height / 10));
    Button stack_button("Stack", font, sf::Vector2f(width / 2, 5*height / 10));
    Button bst_button("Binary Tree", font, sf::Vector2f(width / 2, 6*height / 10));
    Button avl_button("AVL Tree", font, sf::Vector2f(width / 2, 7*height / 10));

    buttons.push_back(list_button);
    buttons.push_back(queue_button);
    buttons.push_back(stack_button);
    buttons.push_back(bst_button);
    buttons.push_back(avl_button);

}