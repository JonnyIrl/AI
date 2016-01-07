#ifndef _BULLET_H_
#define _BULLET_H_

#include "Common.h"
#include "vectorMath.h"
using namespace std;

class BasicBullet
{
private:
	float m_speed, m_timeAlive, m_timeToLive, m_damage , m_rotation, m_friction;
	sf::Vector2f m_pos, m_dir;

	//for drawing sprite
	sf::Sprite m_sprite; //holds the sprite


public:
	BasicBullet(){}
	BasicBullet(sf::Vector2f pos, float rotation, float speed, float m_timeToLive, sf::Texture* texture);
	~BasicBullet()
	{
		cout << "Bullet deleted" << endl;
	}
	bool Update(float time);
	void Draw(sf::RenderWindow& window);


};
#endif