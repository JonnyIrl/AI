#ifndef _MENU_H_
#define _MENU_H_

#include "Common.h"


#include "GameStateController.h"



class Menu
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:

	Menu(int w,int h);
	~Menu()
	{
	
	}
	void Init();
	void Update(float time);
	void Draw(sf::RenderWindow& window);


};
#endif
