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
	screen_width = w; 
	screen_heigth = h;
	for (int i = 0; i < max_Obstacles; i++)
	{
		basicAsteroids->push_back(new Obstacles(sf::Vector2f((rand() % screen_width * 3 - screen_width), (rand() % screen_heigth * 3 - screen_heigth))));
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
void ObstacleManager::Reset()
{
	//delete the old swarm
	for each(Obstacles* o in *basicAsteroids)
	{
		delete o;
	}
	delete basicAsteroids;
	//create new swarm
	basicAsteroids = new list<Obstacles*>();
	for (int i = 0; i < max_Obstacles; i++)
	{
		basicAsteroids->push_back(new Obstacles( sf::Vector2f((rand() % screen_width * 3 - screen_width), (rand() % screen_heigth * 3 - screen_heigth))));
		
	}

}