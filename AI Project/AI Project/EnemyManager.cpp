#include "EnemyManager.h"


bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

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
	for (int i = 0; i < max_Enemies; i++)
	{
		//Enemy e;
		//e.Init(&texture, sf::Vector2f((rand() % w + 21),(rand() % h + 21)));
		basicEnemies.push_back(new Enemy(&texture, sf::Vector2f((rand() % w + 21), (rand() % h + 21))));
	}
}
void EnemyManager::Update(float time , Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for each(Enemy* e in basicEnemies)
	{
		e->Update(time , p );
		
	}
}
void EnemyManager::Draw(sf::RenderWindow& window)
{
	for each(Enemy* e in basicEnemies)
	{
		e->Draw(window);
	}
}