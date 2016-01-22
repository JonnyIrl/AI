#include "PowerupManager.h"
#include "Player.h"
#include <ctime>
#include <cstdlib>
#include <iostream>


bool PowerupManager::instanceFlag = false;
PowerupManager* PowerupManager::instance = NULL;

PowerupManager* PowerupManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new PowerupManager();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void PowerupManager::Init(int w, int h)
{
	srand(time(NULL));
	screen_width = w;
	screen_height = h;
	for (int i = 0; i < max_Powerups; i++)
	{
		int typeOfPowerUp = rand() % 3 + 1;
		std::cout << "POWER UP = " << typeOfPowerUp << endl;

		//If random number == 1 then spawn a SPEED boost powerup
		if (typeOfPowerUp == 1)
			powers->push_back(new Powerup(&speedUpTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % h + 21)), w, h, false, true, false));

		//If random number == 2 then spawn a HEALTH boost powerup
		if (typeOfPowerUp == 2)
			powers->push_back(new Powerup(&healthTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % h + 21)), w, h, true, false, false));

		//If random number == 3 then spawn a SHIELD boost powerup
		if (typeOfPowerUp == 3)
			powers->push_back(new Powerup(&shieldTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % h + 21)), w, h, false, false, true));
	}
}

//float RandomNumber(float Min, float Max)
//{
//	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
//}

void PowerupManager::Update(float time, Player* p)
{
	//cout << p->GetPosition().x << ":" << p->GetPosition().y << endl;
	for (list<Powerup*>::iterator it = powers->begin(); it != powers->end();)
	{
		if ((*it)->IsAlive())
		{
			(*it)->Update(time, p, powers);
			it++;
		}
		else
		{
			delete (*it);
			it = powers->erase(it);
		}
	}

}
void PowerupManager::Draw(sf::RenderWindow& window)
{
	for each(Powerup* p in *powers)
	{
		p->Draw(window);
	}
}
void PowerupManager::Reset()
{
	srand(time(NULL));
	//delete the old swarm
	for each(Powerup* p in *powers)
	{
		delete p;
	}
	delete powers;
	//create new swarm
	powers = new list<Powerup*>();
	for (int i = 0; i < max_Powerups; i++)
	{
		int typeOfPowerUp = rand() % 3 + 1;
		std::cout << "POWER UP = " << typeOfPowerUp << endl;

		//If random number == 1 then spawn a SPEED boost powerup
		if (typeOfPowerUp == 1)
			powers->push_back(new Powerup(&speedUpTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % screen_height + 21)), screen_width, screen_height, false, true, false));

		//If random number == 2 then spawn a HEALTH boost powerup
		if (typeOfPowerUp == 2)
			powers->push_back(new Powerup(&healthTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % screen_height + 21)), screen_width, screen_height, true, false, false));

		//If random number == 3 then spawn a SHIELD boost powerup
		if (typeOfPowerUp == 3)
			powers->push_back(new Powerup(&shieldTexture, sf::Vector2f(float(rand()) / RAND_MAX * 3000 - 1000, (rand() % screen_height + 21)), screen_width, screen_height, false, false, true));

	}

}