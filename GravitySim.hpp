#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include <iostream>
#include "Button.hpp"

 
/*
code adapted from https://www.youtube.com/@zipped1214
*/

class GravitySource
{

public:

    GravitySource() {}
    GravitySource(float pos_x, float pos_y, float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;
 
        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(10);
    }
 
    void render(sf::RenderWindow& window)
    {
        s.setPosition(pos);
        window.draw(s);
    }
 
    sf::Vector2f get_pos()
    {
        return pos;
    }
 
    float get_strength()
    {
        return strength;
    }

    void setPos(sf::Vector2f pos)
    {
        this->pos.x = pos.x;
        this->pos.y = pos.y;
    }

    void setStrength(float strength)
    {
        this->strength = strength;
    }

    void setColor(sf::Color color)
    {
        this->s.setFillColor(color);
    }

    void setRadius(float num)
    {
        s.setRadius(num);
    }

private:

    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;
};


class Particle
{

public:

    Particle() {}
    Particle(float pos_x, float pos_y, float vel_x, float vel_y, Button &shape)
    {
        pos.x = pos_x;
        pos.y = pos_y;
 
        vel.x = vel_x;
        vel.y = vel_y;

        this->shape = shape;
        shape._setPosititon(pos);
    }

    void setShape(Button &shape)
    {
        this->shape = shape;
    }

    bool interaction(sf::Event &event, sf::Window &window)
    {
        return shape.cursorInteraction(event, window);
    }

    void setPos(sf::Vector2f pos)
    {
        this->pos = pos;
        shape._setPosititon(pos);
    }

    void setVel(sf::Vector2f vel)
    {
        this->vel = vel;
    }
 
    void render(sf::RenderWindow& window)
    {
        shape._setPosititon(pos);
        window.draw(shape);
    }

    std::string getText()
    {
        return shape._getText();
    }

    sf::Vector2f getPos()
    {
        return pos;
    }

    sf::Vector2f getVel()
    {
        return vel;
    }

    Button getShape()
    {
        return shape;
    }


    void acceleratePos()
    {
        float deceleration = 0.95f; /* lower value means stronger deceleration */

        if (std::abs(vel.x) < 0.1f && std::abs(vel.y) < 0.1f) {
            vel.x = 0.0f;
            vel.y = 0.0f;
            return;
        }

        vel.x *= deceleration;
        vel.y *= deceleration;

        vel.x = std::abs(vel.x) * direction.x;
        vel.y = std::abs(vel.y) * direction.y; 


        pos.x += vel.x;
        pos.y += vel.y;

    }

    void handleCollisions()
    {

    }

    void setDirection(sf::Vector2i direction)
    {
        this->direction = direction;
    }

    void setDirection_x(int n)
    {
        this->direction.x = n;
    }

    void setDirection_y(int n)
    {
        this->direction.y = n;
    }

    void setVel_x(int n)
    {
        this->vel.x = n;
    }

      void setVel_y(int n)
    {
        this->vel.y = n;
    }

private:

    sf::Vector2i direction;
    sf::Vector2f pos;
    sf::Vector2f vel;
    Button shape;
};