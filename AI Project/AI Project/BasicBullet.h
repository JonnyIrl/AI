#ifndef _BULLET_H_
#define _BULLET_H_

#include "Common.h"
#include "vectorMath.h"
#include "Player.h"
using namespace std;

class BasicBullet
{
private:
	float m_speed, m_timeAlive, m_timeToLive, m_damage, m_rotation, m_friction, m_radius, angleBetween, rotationSpeed;
	sf::Vector2f m_pos, m_dir;

	//for drawing sprite
	sf::Sprite m_sprite; //holds the sprite
	Player* m_target;
public:
	BasicBullet(){}
	BasicBullet(sf::Vector2f pos, float rotation, float speed, float m_timeToLive, sf::Texture* texture);
	BasicBullet(sf::Vector2f pos, float speed, float m_timeToLive, sf::Texture* texture,Player* target);
	~BasicBullet()
	{
		cout << "Bullet deleted" << endl;
	}
	bool Update(float time); 
	bool UpdatePredator(float time);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition();
	float GetRadius();
	void seek(sf::Vector2f target);
	void intercept();
	void Rotate(float time);
};
#endif