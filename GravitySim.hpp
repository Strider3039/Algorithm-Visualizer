#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <iostream>

 
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

private:

    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;
};


class Particle
{

public:

    Particle() {}
    Particle(float pos_x, float pos_y, float vel_x, float vel_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;
 
        vel.x = vel_x;
        vel.y = vel_y;

        s.setPosition(pos);
        s.setFillColor(sf::Color::Magenta);
        s.setRadius(8);
    }

    void setPos(sf::Vector2f pos)
    {
        this->pos = pos;
        s.setPosition(pos);
    }

    void setColor(sf::Color color)
    {
        s.setFillColor(color);
    }

    void setRadius(int num)
    {
        s.setRadius(num);
    }

    void setVel(sf::Vector2f vel)
    {
        this->vel = vel;
    }
 
    void render(sf::RenderWindow& window)
    {
        s.setPosition(pos);
        window.draw(s);
    }

 
    void update_physics(GravitySource& s)
    {
        float distance_x = s.get_pos().x - pos.x;
        float distance_y = s.get_pos().y - pos.y;
 
        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
 
        float inverse_distance = 1.f / distance;
 
        float normalized_x = inverse_distance * distance_x;
        float normalized_y = inverse_distance * distance_y;
 
        float inverse_square_dropoff = inverse_distance * inverse_distance;
 
        float acceleration_x = normalized_x * s.get_strength() * inverse_square_dropoff;
        float acceleration_y = normalized_y * s.get_strength() * inverse_square_dropoff;
 
        vel.x += acceleration_x;
        vel.y += acceleration_y;
 
        pos.x += vel.x;
        pos.y += vel.y;

        std::cout << pos.x << ", " << pos.y << std::endl;
    }

private:

    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape s;
};