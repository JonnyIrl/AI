#include "EnemyManager.h"


bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = nullptr;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void EnemyManager::Init(int w, int h)
{
	for (int i = 0; i < 1; i++)
	{
		Enemy e;
		e.Init(&texture, sf::Vector2f((rand() % w + 21),(rand() % h + 21)));
		basicEnemies.push_back(e);
	}
}
void EnemyManager::Update(float time , Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for each(Enemy e in basicEnemies)
	{
		e.Update(time , p );
		
	}
}
void EnemyManager::Draw(sf::RenderWindow& window)
{
	for each(Enemy e in basicEnemies)
	{
		e.Draw(window);
	}
}