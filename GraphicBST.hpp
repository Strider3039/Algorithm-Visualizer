#pragma once
#include "linkedList.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <atomic>
#include "nodeGraphic.hpp"
#include "Button.hpp"
#include "menuItems.hpp"
#include "textBox.hpp"


template <class T>
class GraphicBST
{
public:

    /*
        Functions:

        Constructor (root, window width, window height) {}

        Insert (data, &font)
            Call private insert 

        Draw (&window)
            call private draw
    */


    GraphicBST();

private:

    /*
        DATA

        struct TreeNode {
            left and right nodes
            shape, text, position

            Constructor (T data, &font, xPos, yPos) : data(data), pLeft(nullptr), pRight(nullptr) {
            
                NODE VISUAL INFORMATION
                setRadius
                setFillColor
                setOutlineColor
                setOutlineThickness
                position = {xPos, yPos};
                setPosition

                LABEL VISUAL INFORMATION
                setfont
                setString
                setCharacterSize
                setFillColor
                getLocalBounds
                setPosition (make sure to center properly)


            
            }
        };

        TreeNode* root
        float windowWidth, windowHeight
        

    */

};