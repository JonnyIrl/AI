#ifndef _POWERUPMANAGER_H
#define _POWERUPMANAGER_H_

#include "Common.h"
#include "Powerup.h"
#include <list>
using namespace std;

class PowerupManager
{
public:
	static PowerupManager* GetInstance();
	~PowerupManager()
	{
		instanceFlag = false;
		for each(Powerup *p in *powers)
		{
			delete p;
		}
		delete powers;
	}
	void Init(int w, int h);
	void Update(float time, Player* p);
	void Draw(sf::RenderWindow& window);
	void Reset();
private:
	static bool instanceFlag;
	static PowerupManager* instance;
	PowerupManager()
	{
		powers = new list<Powerup*>();
		if (!speedUpTexture.loadFromFile("Assets/Powerups/speed.png"))
		{

		}

		if (!healthTexture.loadFromFile("Assets/Powerups/health.png"))
		{

		}

		if (!shieldTexture.loadFromFile("Assets/Powerups/shield.png"))
		{

		}
	}

	sf::Texture speedUpTexture;
	sf::Texture healthTexture;
	sf::Texture shieldTexture;
	list<Powerup*>* powers;
	int max_Powerups = 5;
	int screen_width, screen_height;
	//float RandomNumber(float Min, float Max);
};



#endif