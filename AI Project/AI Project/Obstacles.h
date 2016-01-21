#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_

#include "Common.h"
#include "Pvector.h"
#include "vectorMath.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Player.h"
#include <list>

class Obstacles
{
public:
	Obstacles(sf::Vector2f pos);
	~Obstacles()
	{
		cout << "Deleteing Asteroid" << endl;
	}
	bool IsCollidingWithPlayer(Player* player);
	bool LoadTexture();
	bool IsAlive();
	void Update(sf::Time time, Player* p);
	void Draw(sf::RenderWindow& window);

private:
	sf::Sprite sprite;
	sf::Vector2f m_position;
	float m_radius;
	int noOfHits;
	sf::Texture texture;
	Animation m_asteroidMoveAnimation;
	AnimatedSprite m_asteroidAnimatedSprite;
};


#endif