#ifndef _ENEMEYMANAGER_H_
#define _ENEMEYMANAGER_H_

#include "Common.h"
#include "Enemy.h"
#include "Player.h"
#include <list>
using namespace std;



class EnemyManager
{
private:

	static bool instanceFlag;
	static EnemyManager* instance;
	EnemyManager()
	{
		if (!texture.loadFromFile("Assets/jet2.png"))
		{

		}	
	}

	sf::Texture texture;
	list<Enemy> basicEnemies;



public:
	static EnemyManager* GetInstance();
	~EnemyManager()
	{
		instanceFlag = false;
	}
	void Init(int w, int h);
	void Update(float time, Player* p);
	void Draw(sf::RenderWindow& window);


};
#endif