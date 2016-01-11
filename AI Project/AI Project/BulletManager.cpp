#include "BulletManager.h"




bool BulletManager::instanceFlag = false;
BulletManager* BulletManager::instance = NULL;

BulletManager* BulletManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new BulletManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void BulletManager::Init()
{

}
void BulletManager::AddPlayerBullet(sf::Vector2f pos, float rotation, float speed, float timeToLive)
{
	playerBullets->push_back(new BasicBullet(pos, rotation, speed, timeToLive, &basicBullet_texture));
}
void BulletManager::AddPredatorBullet(sf::Vector2f pos, float speed, float timeToLive,  Player* target)
{
	predatorBullets->push_back(new BasicBullet(pos, speed, timeToLive, &predatorBullet_texture, target));
}
void BulletManager::Update(float time)
{
	
	for (list<BasicBullet*>::iterator it = playerBullets->begin(); it != playerBullets->end();)
	{
		if ((*it)->Update(time))
		{
			it++;
		}
		else
		{
			delete (*it);
			it = playerBullets->erase(it);
		}
		
	}
	for (list<BasicBullet*>::iterator it = predatorBullets->begin(); it != predatorBullets->end();)
	{
		if ((*it)->UpdatePredator(time))
		{
			it++;
		}
		else
		{
			delete (*it);
			it = predatorBullets->erase(it);
		}

	}
}
void BulletManager::Draw(sf::RenderWindow& window)
{
	for each(BasicBullet* b in *playerBullets)
	{
		b->Draw(window);
	}
	for each(BasicBullet* b in *predatorBullets)
	{
		b->Draw(window);
	}
}