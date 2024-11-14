#pragma once
//#include "source.hpp"
#include <SFML/Graphics.hpp>
#include <X11/X.h>
#include <iostream>


/// <summary>
/// Generates border/box around text. Use inherited functions from sf::Text to change position of box, change color of text, etc..
/// Must call window.draw(box.getBox) and window.draw(box.getText) before displaying. Text boxes are invisible and are not centered perfectly around text; ues offset functions to center box.
/// </summary>
class DialogBox : public sf::Text, sf::RectangleShape   
{
public:

	DialogBox()
	{
		// font.loadFromFile("Jersey20-Regular.ttf"); // update 10/21/24 -- loading no specific file should use a default font within SFML
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setString("Default String");
		text.setCharacterSize(40);
		text.setPosition(400, 200);

		bounds = text.getLocalBounds();  
		position = text.getPosition();

		bounds.height * text.getCharacterSize();
		bounds.width* text.getCharacterSize();

		box.setPosition((position.x - 9), position.y); 
		box.setSize(sf::Vector2f((bounds.width + 20), (bounds.height + 23)));
		box.setFillColor(sf::Color::Yellow);

		std::cout << "loaded Default dialog box" << std::endl; 
	}
	DialogBox(sf::String stringToDisplay, sf::Vector2f position, int size) // 10/31/24 -- TODO add param string for loading font file
	{
		font.loadFromFile("DiaryOfAn8BitMage-lYDD.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(5);
		text.setString(stringToDisplay); 
		//text.setCharacterSize(40);
		text.setCharacterSize(size); 
		text.setPosition(position); 

		bounds = text.getLocalBounds(); 


		//bounds.height* text.getCharacterSize();
		//bounds.width* text.getCharacterSize();

		box.setPosition((position.x - 9), (position.y));
		box.setSize(sf::Vector2f((bounds.width + 20), (bounds.height + 23)));
		box.setFillColor(sf::Color::Yellow);
		
		std::string stringForPrintDebugging = stringToDisplay; 
		std::cout << "loaded dialog box with \"" << stringForPrintDebugging << "\"" << std::endl;  
	}
	void setTextColor(sf::Color color)
	{
		text.setFillColor(color); 
	}

	void setBoxColor(sf::Color color) 
	{
		box.setFillColor(color);
	}

	/*void setTextSize(int num)
	{
		text.setCharacterSize(num);
	}*/

	sf::RectangleShape getBox()
	{
		return box;
	}
	sf::Text getText()
	{
		return text; 
	}

	void LoadFontFromFile(const std::string &filePath)
	{
		font.loadFromFile(filePath); 
	}

	/// <summary>
	/// distance in pixels to offset rectangle to the right
	/// </summary>
	void offsetRight(float distance)
	{
		box.setPosition((position.x - distance), position.y);
		position.x = position.x - distance; 
	}
	/// <summary>
	/// distance in pixels to offset bos to left
	/// </summary>
	void offsetLeft(float distance)
	{
		box.setPosition((position.x + distance), position.y);
		position.x = position.x + distance;
	}
	/// <summary>
	/// distance in pixels to offset upwads
	/// </summary>
	void offsetUp(float distance)
	{
		box.setPosition(position.x, (position.y + distance));
		position.y = position.y + distance;
	}
	/// <summary>
	/// distance in pixels to offset downwards
	/// </summary>
	void offsetDown(float distance)
	{
		box.setPosition(position.x, (position.y - distance));
		position.y = position.y - distance;
	}
	/// <summary>
	/// change the texture of the box
	/// </summary>
	/// <param name="texture"></param>
	void changeTexture(sf::Texture* texture )
	{
		box.setTexture(texture);
	}
	/// <summary>
	/// adjust the height of the box. +num to increase, -num to decrease size
	/// </summary>
	/// <param name="difference"></param>
	void changeHeight(float difference)
	{
		sf::Vector2f dimensions = box.getSize(); 
		box.setSize(sf::Vector2f(dimensions.x, (dimensions.y + difference)));
	}
	/// <summary>
	/// adjust the height of the box. +num to increase, -num to decrease size
	/// </summary>
	/// <param name="difference"></param>
	void changeWidth(float difference)
	{
		sf::Vector2f dimensions = box.getSize(); 
		box.setSize(sf::Vector2f((dimensions.x + difference), dimensions.y)); 
	}
	/// <summary>
	/// temp for making origin visible
	/// </summary>
	sf::CircleShape getOriginPoint()
	{
		return originPoint; 
	}
private:


	sf::RectangleShape box;
	sf::FloatRect bounds; 
	sf::String stringToDisplay; 
	sf::Text text;
	sf::Font font;
	sf::Vector2f position;

	//temp
	sf::CircleShape originPoint;

};