#ifndef _MENU_H_
#define _MENU_H_

#include "Common.h"


#include "GameStateController.h"



class Menu
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture playTexture, controlsTexture, quitTexture;
	sf::RectangleShape playRectangle, quitRectangle, controlsRectangle;
	sf::Event Event;
public:

	Menu(int w,int h);
	~Menu()
	{
	
	}
	void Init();
	void Update(float time, sf::RenderWindow& window, sf::Event Event);
	void Draw(sf::RenderWindow& window);
	bool LoadTextures();


};
#endif
