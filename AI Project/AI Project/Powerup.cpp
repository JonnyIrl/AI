#include "Powerup.h"

Powerup::Powerup()
{
}

Powerup::~Powerup()
{
	std::cout << "POWER UP DELETED" << std::endl;
}

Powerup::Powerup(sf::Texture* texture, sf::Vector2f pos, float width, float height, bool isHealth, bool isSpeed, bool isShield)
{
	sf::Vector2u size = texture->getSize();
	m_Radius = (sqrt((size.x* size.x) + (size.y * size.y))) / 2;
	sprite.setTexture(*texture);
	m_Position = pos;
	sprite.setPosition(m_Position);
	noOfHits = 0;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	playerHealth = isHealth;
	playerShield = isShield;
	playerPowerSpeedUpActive = isSpeed;
	enemeyPowerSpeedUpActive = isSpeed;

	std::cout << "POWER UP LOCATION = " << m_Position.x << "," << m_Position.y << endl;
}

void Powerup::Update(float time, Player* p, list<Powerup*>* v)
{

	//Checks collision with the player.
	if (IsCollidingWithPlayer(p))
	{
		noOfHits++;

		//If its the players health power up then increase the players health
		if (playerHealth)
		{
			p->PlayerIncreaseHealth();
		}

		//If its the players shield power up then increase the players shield
		if (playerShield)
		{
			p->PlayerIncreaseShield();
		}

		//If its the players speed power up then increase the players max speed
		if (playerPowerSpeedUpActive)
		{
			p->RestartClock();
			playerPowerSpeedUpActive = false;
		}
	}

	sprite.setPosition(m_Position);
}


void Powerup::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	sprite.setPosition(m_Position);
}

sf::Vector2f  Powerup::GetPosition()
{
	return sprite.getPosition();
}

void Powerup::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Powerup::IsCollidingWithPlayer(Player* p)
{

	if (sprite.getGlobalBounds().intersects(p->GetRectangle().getGlobalBounds()))
	{
		std::cout << "Player hit the Powerup" << endl;
		return true;
	}

	return false;
}


bool Powerup::IsAlive()
{
	if (noOfHits >= 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}