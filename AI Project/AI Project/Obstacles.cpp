#include "Obstacles.h"

using namespace std;

Obstacles::Obstacles(sf::Vector2f pos)
{
	if (LoadTexture())
	{
		m_asteroidMoveAnimation.setSpriteSheet(texture);
		m_asteroidMoveAnimation.addFrame(sf::IntRect(0, 0, 125, 125));
		m_asteroidMoveAnimation.addFrame(sf::IntRect(125, 0, 125, 125));
		m_asteroidMoveAnimation.addFrame(sf::IntRect(250, 0, 125, 125));
		m_asteroidMoveAnimation.addFrame(sf::IntRect(375, 0, 125, 125));
		m_asteroidMoveAnimation.addFrame(sf::IntRect(500, 0, 125, 125));


		m_asteroidAnimatedSprite = AnimatedSprite(sf::seconds(0.13f));
		m_asteroidAnimatedSprite.setAnimation(m_asteroidMoveAnimation);

		//Setup the sprite.
		m_position = pos;
		sprite.setPosition(m_position);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 125, 125));
		sprite.setScale(sf::Vector2f(0.5f, 0.5f));
		m_asteroidAnimatedSprite.setPosition(sprite.getPosition());
		m_asteroidAnimatedSprite.setScale(sprite.getScale());
		m_asteroidAnimatedSprite.setColor(sf::Color::White);

	}

	else
	{
		cout << "Failed to load asteroid sprite sheet" << endl;
	}
}

void Obstacles::Update(sf::Time time, Player* p)
{
	m_asteroidAnimatedSprite.update(time);

	if (IsCollidingWithPlayer(p))
	{
		noOfHits++;
	}
}

void Obstacles::Draw(sf::RenderWindow& window)
{
	window.draw(m_asteroidAnimatedSprite);
}

bool Obstacles::LoadTexture()
{
	if (!texture.loadFromFile("Assets/Asteroid/spriteSheet.png"))
		return false;

	else
		return true;
}

bool Obstacles::IsCollidingWithPlayer(Player* p)
{
	if (sprite.getGlobalBounds().intersects(p->GetRectangle().getGlobalBounds()))
	{
		std::cout << "Asteroid hit the player" << endl;
		return true;
	}

	return false;
}

bool Obstacles::IsAlive()
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
