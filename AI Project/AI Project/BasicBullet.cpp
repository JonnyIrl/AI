#include "BasicBullet.h"

BasicBullet::BasicBullet(sf::Vector2f pos, float rotation, float speed, float timeToLive, sf::Texture* texture)
{
	//float m_speed, m_timeAlive, m_timeToLive, m_damage, m_rotation;
	//sf::Vector2f m_pos, m_dir;
	m_pos = pos;
	m_speed = speed;
	m_timeToLive = timeToLive;
	m_timeAlive = 0;
	m_sprite.setTexture(*texture);
	m_friction = -10;
	m_rotation = rotation;
	m_dir = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(m_rotation)), sin(VectorMath::GetInstance()->ToRadian(m_rotation))));
	sf::Vector2u size = texture->getSize();
	m_sprite.setOrigin(size.x/2,size.y/2);
	m_sprite.setRotation(m_rotation);
	m_sprite.setPosition(m_pos);
}
void BasicBullet::Update(float time)
{
	//s=ut+(1/2)a(t(t))
	m_pos += m_dir * m_speed * time + m_dir * 0.5f* m_friction * time *time;
	m_speed += m_friction* time;
	m_sprite.setPosition(m_pos);
}
void BasicBullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}