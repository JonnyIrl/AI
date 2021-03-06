
#include "FactoryManager.h"
#include "Player.h"

bool FactoryManager::instanceFlag = false;
FactoryManager* FactoryManager::instance = NULL;

FactoryManager* FactoryManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new FactoryManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void FactoryManager::Init(int w, int h)
{
	screen_heigth = h;
	screen_width = w;
	for (int i = 0; i < max_Factories; i++)
	{
		factories->push_back(new FactoryShip(&factoryTexture, sf::Vector2f((rand() % w * 3 -w), (rand() % h * 3 - h)), w, h));
	}
}
void FactoryManager::Update(float time, Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for (list<FactoryShip*>::iterator it = factories->begin(); it != factories->end();)
	{
		if ((*it)->IsAlive())
		{
			(*it)->Update(time, p, factories);
			it++;
		}
		else
		{
			delete (*it);
			it = factories->erase(it);
		}

	}
	
}
void FactoryManager::Draw(sf::RenderWindow& window)
{
	for each(FactoryShip* f in *factories)
	{
		f->Draw(window);
	}
}

bool FactoryManager::IsColiding(BasicBullet* b)
{
	for each(FactoryShip* f in *factories)
	{
		if (f->IsColiding(b->GetPosition(), b->GetRadius()))
		{
			return true;
		}
	}
	return false;
}
void FactoryManager::Reset()
{
	//delete the old swarm
	for each(FactoryShip* f in *factories)
	{
		delete f;
	}
	delete factories;
	//create new swarm
	factories = new list<FactoryShip*>();
	for (int i = 0; i < max_Factories; i++)
	{
		factories->push_back(new FactoryShip(&factoryTexture, sf::Vector2f((rand() % screen_width * 3 - screen_width), (rand() % screen_heigth * 3 - screen_heigth)), screen_width, screen_heigth));

	}

}