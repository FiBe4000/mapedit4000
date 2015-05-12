#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "oldTile.h"

using namespace std;

void RenderTiles(int x, int y, sf::Sprite& sprite, sf::Sprite& emptyTileSprite, sf::RenderWindow& App);
void SaveMap();
string GetMapInfo();

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
int LevelWidth;
int LevelHeight;
int PlayerX = 10;
int PlayerY = 10;
int TimeLimit = 100;
char filename[30];
vector< vector<Tile> > level;

int main()
{
    int imNumber = 0;
    int x = 1;
    int y = 1;
    int TimeLimit;
    bool IsAccessible = true;
    bool Running = true;
    bool LastLoop = false;
    bool UpLast = false;
    bool DownLast = false;
    bool CLast = false;
    bool DLast = false;
    bool GLast = false;
    bool SLast = false;
    bool FLast = false;
    bool Death = false;
    bool NewLevel = false;

    sf::Event event;
    sf::Texture emptyTileIm;
    sf::Texture Tileset;
    sf::Texture InfoBar;
    sf::Sprite CurrentTileSprite;
    sf::Sprite sprite;
    sf::Sprite emptyTileSprite;
    sf::Sprite InfoSprite;
    sf::View view1;
    sf::Vector2f MousePos;
    sf::String col;
    sf::Font font;
    sf::Clock frameClock;

    cout << "Level Width: ";
    cin >> LevelWidth;
    cout << "Level Height: ";
    cin >> LevelHeight;
    cout << "Time Limit: ";
    cin >> TimeLimit;
    cout << "Filename: ";
    cin >> filename;

    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Map Editor");//, sf::Style::Fullscreen);
    App.setVerticalSyncEnabled(true);

    emptyTileIm.loadFromFile("gfx/emptyTile.png");
    emptyTileIm.setSmooth(false);
    emptyTileSprite.setTexture(emptyTileIm);
    Tileset.loadFromFile("gfx/tileset2.png");
    Tileset.setSmooth(false);
    InfoBar.loadFromFile("gfx/InfoBar.png");
    InfoBar.setSmooth(false);
    InfoSprite.setTexture(InfoBar);
    InfoSprite.setPosition(0,0);
    sprite.setTexture(Tileset);
    CurrentTileSprite.setTexture(Tileset);
    CurrentTileSprite.setTextureRect(sf::Rect<int>(imNumber*32, 0, 32, 32));
    CurrentTileSprite.setPosition(10,4);

    view1.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    App.setView(view1);

    for(int n=0; n<LevelHeight; n++)
   	{
   	   	std::vector<Tile> newVector;
   	    level.push_back(newVector);
   	}
    for(int i=0; i<LevelHeight; i++)
    {
        for(int n=0; n<LevelWidth; n++)
        {
            Tile newTile(9,1,"",(sf::Vector2u(Tileset.getSize().x / TILE_WIDTH, Tileset.getSize().y / TILE_HEIGHT)));
            level[i].push_back(newTile);
        }
    }
                while(Running)
                {
                	frameClock.restart();
                	
                    App.pollEvent(event);
                    
                    bool EscapeKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
                    
                    bool LeftButtonDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                    
                    bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
                    bool DownKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
                    
                    bool CKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
                    bool DKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
                    bool GKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
                    bool SKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
                    bool FKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
					
					
                    MousePos = App.mapPixelToCoords(sf::Mouse::getPosition(App));

                    if(EscapeKeyDown)
                    {
                        Running = false;
                    }
                    //cout << "x: " << x << "  y: " << y << endl;

                    if(sf::Mouse::getPosition().x > WINDOW_WIDTH-10)
                    {
                        x+= 3;
                    }
                    else if(sf::Mouse::getPosition().x < 10)
                    {
                        x-= 3;
                    }
                    if(sf::Mouse::getPosition().y > WINDOW_HEIGHT-10)
                    {
                        y+= 3;
                    }
                    else if(sf::Mouse::getPosition().y < 10)
                    {
                        y-= 3;
                    }
                    if(LeftButtonDown && MousePos.x >= 0 && MousePos.y >= 0 && MousePos.y < LevelHeight*TILE_HEIGHT && MousePos.x < LevelWidth*TILE_WIDTH)
                    {
                        MousePos = App.mapPixelToCoords(sf::Mouse::getPosition(App));
                        level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].imNumber = imNumber;
                        level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].IsAccessible = IsAccessible;
                        level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].isClicked = true;
                        level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].Death = Death;
                        level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].NewLevel = NewLevel;
                        //cout << int(MousePos.y/TILE_HEIGHT) << " , " << int(MousePos.x/TILE_WIDTH) << endl;
                        //cout << level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].imNumber;
                        //cout << IsAccessible;
                        //cout << level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].x << endl;
                        //cout << level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].y << endl;
                    }
                    //sf::Vector2f MousePos = App.ConvertCoords(sf::Mouse::getPosition(App).x, sf::Mouse::getPosition(App).y);
                    //cout << level[int(MousePos.y/TILE_HEIGHT)][int(MousePos.x/TILE_WIDTH)].IsAccessible;
                    if(CKeyDown && !CLast)
                    {
                        if(IsAccessible)
                            IsAccessible = false;
                        else
                            IsAccessible = true;
                    }
                    if(DKeyDown && !DLast)
                    {
                        if(Death)
                            Death = false;
                        else
                            Death = true;
                    }
                    if(GKeyDown && !GLast)
                    {
                        if(NewLevel)
                            NewLevel = false;
                        else
                            NewLevel = true;
                    }
                    if(SKeyDown && !SLast)
                    {
                        SaveMap();
                    }
                    if(FKeyDown && !FLast)
                    {
                    	for(int i=0; i<LevelHeight; i++)
                    	{
                    	    for(int n=0; n<LevelWidth; n++)
                    	    {
                    	    	level[i][n].imNumber = imNumber;
                    	    	level[i][n].IsAccessible = IsAccessible;
                    	    	level[i][n].isClicked = true;
                    	    	level[i][n].Death = Death;
                    	    	level[i][n].NewLevel = NewLevel;
                    	    }
                    	}
                    }
                    if(UpKeyDown && !UpLast)
                    {
                        imNumber++;
                        //CurrentTileSprite.setTextureRect(sf::Rect<int>(imNumber*32, 0, 32, 32));
                    }
                    if(DownKeyDown && imNumber > 0 && !DownLast)
                    {
                        imNumber--;
                        //CurrentTileSprite.setTextureRect(sf::Rect<int>(imNumber*32, 0, 32, 32));
                    }
                    
                    int top = 0;
					int left = (imNumber % (Tileset.getSize().x / TILE_WIDTH)) * TILE_WIDTH;
		
					while(imNumber >= (top * (Tileset.getSize().x / TILE_WIDTH)))
					{
						top++;
					}
					top -= 1;
					top *= TILE_HEIGHT;
	
					CurrentTileSprite.setTextureRect(sf::Rect<int>(left, top, TILE_WIDTH, TILE_HEIGHT));

                    LastLoop = LeftButtonDown;
                    UpLast = UpKeyDown;
                    DownLast = DownKeyDown;
                    CLast = CKeyDown;
                    DLast = DKeyDown;
                    GLast = GKeyDown;
                    SLast = SKeyDown;
					FLast = FKeyDown;

                    view1.setCenter(x,y);
                    App.clear();
                    RenderTiles(x, y, sprite, emptyTileSprite, App);

                    App.setView(App.getDefaultView());
                    App.draw(InfoSprite);
                    App.draw(CurrentTileSprite);
                    App.setView(view1);

                    App.display();
                }

    return 0;
}

void RenderTiles(int x, int y, sf::Sprite& sprite, sf::Sprite& emptyTileSprite, sf::RenderWindow& App)
{
   int extra_offsetXa = 1;
   int extra_offsetXb = 1;
   int extra_offsetYa = 1;
   int extra_offsetYb = 1;

   int Xa = int( -0.5f+((float)x-(float)WINDOW_WIDTH/2)/(float)TILE_WIDTH ) -extra_offsetXa;
   int Xb = int( 0.5f+((float)x+(float)WINDOW_WIDTH/2)/(float)TILE_WIDTH ) +extra_offsetXb;

   int Ya = int( -0.5f+((float)y-(float)WINDOW_HEIGHT/2)/(float)TILE_HEIGHT ) -extra_offsetYa;
   int Yb = int( 0.5f+((float)y+(float)WINDOW_HEIGHT/2)/(float)TILE_HEIGHT ) +extra_offsetYb;

   // If the variables isn't in range, make them so.
   (Xa < 0) ? Xa=0 : 0;
   (Xb > LevelWidth) ? Xb=LevelWidth : 0;
   (Ya < 0) ? Ya=0 : 0;
   (Yb > LevelHeight) ? Yb=LevelHeight : 0;

   for(int i=Xa; i<Xb; i++)
   {
      for(int j=Ya; j<Yb; j++)
      {
         // Set position
         sprite.setPosition(i*TILE_WIDTH, j*TILE_HEIGHT);
         sprite.setTextureRect( level[j][i].GetRect() );
         if(level[j][i].isClicked)
         {
            App.draw(sprite);
            if(!level[j][i].IsAccessible)
            {
                //sf::Shape ColShape;
                sf::RectangleShape rect(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
                
                rect.setPosition(sprite.getPosition());
                rect.setFillColor(sf::Color(255,0,0,100));
                
                App.draw(rect);
            }
            if(level[j][i].Death)
            {
                //sf::Shape DeathShape;
                sf::RectangleShape deathRect(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
                
                deathRect.setPosition(sprite.getPosition());
                deathRect.setFillColor(sf::Color(0,255,0,100));
                
                App.draw(deathRect);
            }
            if(level[j][i].NewLevel)
            {
                //sf::Shape NLevelShape; 
                sf::RectangleShape nLevelRect(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
                
                nLevelRect.setPosition(sprite.getPosition());
                nLevelRect.setFillColor(sf::Color(0,0,255,100));
                
                App.draw(nLevelRect);
            }
         }
         else
         {
             emptyTileSprite.setPosition(i*TILE_WIDTH, j*TILE_HEIGHT);
             App.draw(emptyTileSprite);
         }
      }
   }
}

void SaveMap()
{
    string mapInfo;
    mapInfo = GetMapInfo();

    ofstream OutFile;

    OutFile.open(filename);

    OutFile << mapInfo;

    OutFile.close();
}

string GetMapInfo()
{
    string mapInfo;
    stringstream Info;

    Info << "Tileset: \"gfx/tileset2.png\"\nLevelWidth: " << LevelWidth <<
            "\nLevelHeight: " << LevelHeight << "\nPlayerX: " << PlayerX <<
            "\nPlayerY: " << PlayerY << "\nTimeLimit: " << TimeLimit << "\n\n";

    for(int i=0; i<LevelHeight; i++)
    {
        for(int n=0; n<LevelWidth; n++)
        {
            if(level[i][n].Death)
                Info << "<" << level[i][n].imNumber << "," << level[i][n].IsAccessible << ",\"PlayerDeath\"> ";
            else if(level[i][n].NewLevel)
                Info << "<" << level[i][n].imNumber << "," << level[i][n].IsAccessible << ",\"LEVEL\"> ";
            else
                Info << "<" << level[i][n].imNumber << "," << level[i][n].IsAccessible << ",\"\"> ";
        }
        Info << "\n";
    }

    mapInfo = Info.str();
    return mapInfo;
}
