#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include "Common.h"
#include <list>
#include "BasicBullet.h"
#include "Player.h"

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
		if (!predatorBullet_texture.loadFromFile("Assets/predatorbullet.png"))
		{
			cout << "predator bullet texture did not load" << endl;
		}
		
		playerBullets = new list<BasicBullet*>();
		predatorBullets = new list<BasicBullet*>();
	}

	sf::Texture basicBullet_texture;
	sf::Texture predatorBullet_texture;
	list<BasicBullet*>* playerBullets;
	list<BasicBullet*>* predatorBullets;


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
		for each(BasicBullet* b in *predatorBullets)
		{
			delete b;
		}
		delete predatorBullets;
		delete instance;
	}
	void Init();
	void AddPlayerBullet(sf::Vector2f pos, float rotation, float speed, float timeToLive);
	void AddPredatorBullet(sf::Vector2f pos,  float speed, float timeToLive, Player* target);
	void Update(float time);
	void Draw(sf::RenderWindow& window);
	void reset();

};
#endif