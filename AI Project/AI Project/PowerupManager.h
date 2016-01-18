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

private:
	static bool instanceFlag;
	static PowerupManager* instance;
	PowerupManager()
	{
		powers = new list<Powerup*>();
		if (!powerupTexture.loadFromFile("Assets/Powerups/speed.png"))
		{

		}
	}

	sf::Texture powerupTexture;
	list<Powerup*>* powers;
	int max_Powerups = 10;
};



#endif