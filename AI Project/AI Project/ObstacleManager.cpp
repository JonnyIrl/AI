#include "ObstacleManager.h"


bool ObstacleManager::instanceFlag = false;
ObstacleManager* ObstacleManager::instance = NULL;

ObstacleManager* ObstacleManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ObstacleManager();
		instanceFlag = true;
		return instance;
	}

	else
	{
		return instance;
	}
}
void ObstacleManager::Init(int w, int h)
{
	for (int i = 0; i < max_Obstacles; i++)
	{
		basicAsteroids->push_back(new Obstacles(sf::Vector2f((rand() % w + 21), (rand() % h + 21))));
	}

}
void ObstacleManager::Update(sf::Time time, Player* p)
{

	for (list<Obstacles*>::iterator it = basicAsteroids->begin(); it != basicAsteroids->end();)
	{
		if ((*it)->IsAlive())
		{
			(*it)->Update(time, p);
			it++;
		}
		else
		{
			delete (*it);
			it = basicAsteroids->erase(it);
		}

	}
}

void ObstacleManager::Draw(sf::RenderWindow& window)
{
	for each(Obstacles* o in *basicAsteroids)
	{
		o->Draw(window);
	}

}