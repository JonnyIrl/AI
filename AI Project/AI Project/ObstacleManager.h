#ifndef _OBSTACLEMANAGER_H_
#define _OBSTACLEMANAGER_H_

#include "Common.h"
#include "Obstacles.h"
#include "Player.h"
#include <list>
using namespace std;

class ObstacleManager
{
public:
	~ObstacleManager()
	{
		instanceFlag = false;
		for each(Obstacles* e in *basicAsteroids)
		{
			delete e;
		}
		delete basicAsteroids;
	}

	static ObstacleManager* GetInstance();

	void Init(int w, int h);
	void Update(sf::Time time, Player* p);
	void Draw(sf::RenderWindow& window);
	void Reset();
private:
	static bool instanceFlag;
	static ObstacleManager* instance;
	int screen_width, screen_heigth;
	ObstacleManager()
	{
		basicAsteroids = new list<Obstacles*>();
		if (!texture.loadFromFile("Assets/Asteroid/spriteSheet.png"))
		{

		}
	}

	sf::Texture texture;
	list<Obstacles*>* basicAsteroids;
	int max_Obstacles = 10;
	

};

#endif

