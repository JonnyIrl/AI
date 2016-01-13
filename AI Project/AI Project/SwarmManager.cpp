
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

	for (int i = 0; i < max_Swarms; i++)
	{
		swarms->push_back(new SwarmBoids(&factoryTexture, sf::Vector2f((rand() % w + 21), (rand() % h + 21)), w, h));
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