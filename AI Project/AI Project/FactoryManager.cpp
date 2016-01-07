#include "FactoryManager.h"


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

	for (int i = 0; i < max_Factories; i++)
	{
		factories->push_back(new FactoryShip(&factoryTexture, sf::Vector2f((rand() % w + 21), (rand() % h + 21)), w, h));
	}
}
void FactoryManager::Update(float time, Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	
	for each(FactoryShip* f in *factories)
	{
		f->Update(time, p, factories);
	}
}
void FactoryManager::Draw(sf::RenderWindow& window)
{
	for each(FactoryShip* f in *factories)
	{
		f->Draw(window);
	}
}