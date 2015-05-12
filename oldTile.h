#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

#define T_WIDTH 32
#define T_HEIGHT 32

class Tile
{
private:

    std::string fileName;

public:
    Tile();
    Tile(int num, bool isAccessible, std::string fName, sf::Vector2u tileSetSize);
    ~Tile();

    int imNumber;
    sf::Rect<int> rect;
    sf::Vector2u tSetSize;
    bool IsAccessible;
    bool isClicked;
    bool Death;
    bool NewLevel;

    std::string GetFileName();

    sf::Rect<int> GetRect();

    const bool isAccessible() const { return IsAccessible; }
};

#endif // TILE_H_INCLUDED
