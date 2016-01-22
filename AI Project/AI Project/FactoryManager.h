#ifndef _FACTORYMANAGER_H_
#define _FACTORYMANAGER_H_

#include "Common.h"
#include "FactoryShip.h"
#include "BasicBullet.h"
#include <list>
using namespace std;



class FactoryManager
{
private:

	static bool instanceFlag;
	static FactoryManager* instance;
	FactoryManager()
	{
		factories = new list<FactoryShip*>();
		if (!factoryTexture.loadFromFile("Assets/factory.png"))
		{

		}
	}

	sf::Texture factoryTexture;
	list<FactoryShip*>* factories;
	int max_Factories = 10;
	int screen_width, screen_heigth;

public:
	static FactoryManager* GetInstance();
	~FactoryManager()
	{
		instanceFlag = false;
		for each(FactoryShip* f in *factories)
		{
			delete f;
		}
		delete factories;
	}
	void Init(int w, int h);
	void Update(float time, Player* p);
	void Draw(sf::RenderWindow& window);
	bool IsColiding(BasicBullet* b);
	void Reset();

};
#endif