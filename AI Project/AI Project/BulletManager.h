#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include "Common.h"
#include <list>
#include "BasicBullet.h"

using namespace std;



class BulletManager
{
private:

	static bool instanceFlag;
	static BulletManager* instance;
	BulletManager()
	{
		if (!basicBullet_texture.loadFromFile("Assets/bullet.png"))
		{
			cout << "bullet texture did not load" << endl;
		}
		playerBullets = new list<BasicBullet*>();
	}

	sf::Texture basicBullet_texture;
	list<BasicBullet*>* playerBullets;


public:
	static BulletManager* GetInstance();
	~BulletManager()
	{
		instanceFlag = false;
		for each(BasicBullet* b in *playerBullets)
		{
			delete b;
		}
		delete playerBullets;
		delete instance;
	}
	void Init();
	void AddPlayerBullet(sf::Vector2f pos, float rotation, float speed, float timeToLive);
	void Update(float time);
	void Draw(sf::RenderWindow& window);


};
#endif