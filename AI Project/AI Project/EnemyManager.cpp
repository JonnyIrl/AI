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
		basicEnemies->push_back(new Enemy(&texture, sf::Vector2f((rand() % w*3 - w), (rand() % h*3 - h))));
	}
	screen_Width = w;
	screen_Height = h;
}
void EnemyManager::Update(float time , Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for each(Enemy* e in *basicEnemies)
	{
		e->Update(time , p );
	}

}

void EnemyManager::AddPredator(sf::Vector2f pos)
{
	basicEnemies->push_back(new Enemy(&texture, pos));
}
void EnemyManager::Draw(sf::RenderWindow& window)
{
	for each(Enemy* e in *basicEnemies)
	{
		e->Draw(window);
	}

}
void EnemyManager::reset()
{
	for each(Enemy* e in *basicEnemies)
	{
		delete e;
	}
	delete basicEnemies;

	basicEnemies = new list<Enemy*>();
	for (int i = 0; i < max_Enemies; i++)
	{
		basicEnemies->push_back(new Enemy(&texture, sf::Vector2f((rand() % screen_Width*3 - screen_Width), (rand() % screen_Height*3 - screen_Height))));
	}
}