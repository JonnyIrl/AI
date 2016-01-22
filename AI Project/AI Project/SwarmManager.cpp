
#include "SwarmManager.h"
#include "Player.h"

bool SwarmManager::instanceFlag = false;
SwarmManager* SwarmManager::instance = NULL;

SwarmManager* SwarmManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SwarmManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void SwarmManager::Init(int w, int h)
{
	screen_width = w;
	screen_heigth = h;
	for (int i = 0; i < max_Swarms; i++)
	{
		swarms->push_back(new SwarmBoids(&factoryTexture, sf::Vector2f((rand() % screen_width * 3 - screen_width), (rand() % screen_heigth * 3 - screen_heigth)), screen_width, screen_heigth));
	}
}
void SwarmManager::Update(float time, Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for (list<SwarmBoids*>::iterator it = swarms->begin(); it != swarms->end();)
	{
		if ((*it)->IsAlive())
		{
			(*it)->Update(time, p, swarms);
			it++;
		}
		else
		{
			delete (*it);
			it = swarms->erase(it);
		}

	}

}
void SwarmManager::Draw(sf::RenderWindow& window)
{
	for each(SwarmBoids* s in *swarms)
	{
		s->Draw(window);
	}
}

bool SwarmManager::IsColiding(BasicBullet* b)
{
	for each(SwarmBoids* s in *swarms)
	{
		if (s->IsColiding(b->GetPosition(), b->GetRadius()))
		{
			return true;
		}
	}
	return false;
}
void SwarmManager::Reset()
{
	//delete the old swarm
	for each(SwarmBoids* s in *swarms)
	{
		delete s;
	}
	delete swarms;
	//create new swarm
	swarms = new list<SwarmBoids*>();
	for (int i = 0; i < max_Swarms; i++)
	{
		swarms->push_back(new SwarmBoids(&factoryTexture, sf::Vector2f((rand() % screen_width*3 - screen_width), (rand() % screen_heigth *3 - screen_heigth)), screen_width, screen_heigth));
	}

}