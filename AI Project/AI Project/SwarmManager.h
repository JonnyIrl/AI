#ifndef _SWARMMANAGER_H_
#define _SWARMMANAGER_H_

#include "Common.h"
#include "SwarmBoids.h"
#include "BasicBullet.h"
#include <list>
using namespace std;



class SwarmManager
{
private:

	static bool instanceFlag;
	static SwarmManager* instance;
	SwarmManager()
	{
		swarms = new list<SwarmBoids*>();
		if (!factoryTexture.loadFromFile("Assets/Swarm/swarm.png"))
		{

		}
	}

	sf::Texture factoryTexture;
	list<SwarmBoids*>* swarms;
	int max_Swarms = 20;
	int screen_width, screen_heigth;

public:
	static SwarmManager* GetInstance();
	~SwarmManager()
	{
		instanceFlag = false;
		for each(SwarmBoids* s in *swarms)
		{
			delete s;
		}
		delete swarms;
	}
	void Init(int w, int h);
	void Update(float time, Player* p);
	void Draw(sf::RenderWindow& window);
	bool IsColiding(BasicBullet* b);
	void Reset();

};
#endif