#ifndef _SCORESCREEN_H_
#define _SCORESCREEN_H_

#include "Common.h"

#include "GameStateController.h"



class ScoreScreen
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:

	ScoreScreen(int w, int h);
	~ScoreScreen()
	{
		
	}
	void Init();
	void Update();
	void Draw(sf::RenderWindow& window);


};
#endif
