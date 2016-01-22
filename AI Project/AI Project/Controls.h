#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include "Common.h"


#include "GameStateController.h"



class Controls
{
private:
	sf::Sprite sprite;
	sf::Texture playTexture, texture;
	sf::RectangleShape playRectangle;
public:

	Controls(int w, int h);
	~Controls()
	{

	}
	void Init();
	void Update(float time, sf::RenderWindow& window, sf::Event Event);
	void Draw(sf::RenderWindow& window);
	bool LoadTextures();


};
#endif
