#include "oldTile.h"
#include <iostream>
#include <string>

Tile::Tile()
{
    IsAccessible = false;
    imNumber = 1;
}

Tile::Tile(int num, bool isAccessible, std::string fName, sf::Vector2u tileSetSize)
{
    isClicked = false;
    Death = false;
	fileName = fName;
    IsAccessible = isAccessible;
    tSetSize = tileSetSize;
    
    int top = 0;
    int left = (num % tSetSize.x) * T_WIDTH;
    
    while(num >= (top * (tSetSize.x)))
    {
    	top++;
    }
    top -= 1;
	top *= T_HEIGHT;
	
    rect = sf::Rect<int>(left, top, T_WIDTH, T_HEIGHT);
}

Tile::~Tile()
{
}

std::string Tile::GetFileName()
{
	std::string tempStr = "";
	int i = 0;

	while(fileName[i] != '\0')
	{
		tempStr += fileName[i];
		i++;
	}

	return tempStr;
}

sf::Rect<int> Tile::GetRect()
{
    int top = 0;
    int left = (imNumber % tSetSize.x) * T_WIDTH;
    
    while(imNumber >= (top * (tSetSize.x)))
    {
    	top++;
    }
    top -= 1;
	top *= T_HEIGHT;
	
    rect = sf::Rect<int>(left, top, T_WIDTH, T_HEIGHT);
	
	return rect;
}

