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
void BulletManager::Update(float time)
{
	for each(BasicBullet* b in *playerBullets)
	{
		 b->Update(time);
	}
}
void BulletManager::Draw(sf::RenderWindow& window)
{
	for each(BasicBullet* b in *playerBullets)
	{
		b->Draw(window);
	}
}