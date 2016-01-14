#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_

#include "Common.h"
#include "Pvector.h"
#include "vectorMath.h"
#include "Player.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include <list>

class Obstacles
{
public:
	Obstacles();
	~Obstacles();
	bool IsCollidingWithPlayer(Player* p);
	bool LoadTexture();
	void Update(sf::Time time);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	Animation m_asteroidMoveAnimation;
	AnimatedSprite m_asteroidAnimatedSprite;
};


#endif