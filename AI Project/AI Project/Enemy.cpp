#include "Enemy.h"


Enemy::Enemy()
{
	if (!texture.loadFromFile("Assets/jet2.png"))
	{

	}
	sf::Vector2u size = texture.getSize();
	m_Radius = (sqrt((size.x* size.x) + (size.y * size.y))) / 2;
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	maxSpeed = 50;
	speed = 100;
	orientation = 0;
	angleBetween = 0;
	acceleration = 0;
	rotationSpeed = 100;
	m_Direction = sf::Vector2f(1, 0);
}
void Enemy::Update(float time, sf::Vector2f target)
{
	seek(target);
	Rotate(time);
	move(time);
	KeepInBounds();
	sprite.setPosition(m_Position);
}
void Enemy::move(float time)
{
	m_Position += (m_Direction * speed  * time) + 0.5F * (acceleration * VectorMath::GetInstance()->Normalise(m_Direction)) * time * time;
}
void Enemy::KeepInBounds()
{
	if (m_Position.x + 36 < 0){ m_Position.x = 800 + 36; }
	else if (m_Position.x > 800 + 36){ m_Position.x = -36; }
	if (m_Position.y + 36 < 0){ m_Position.y = 600 + 36; }
	else if (m_Position.y > 600 + 36){ m_Position.y = -36; }
}
void Enemy::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	sprite.setPosition(m_Position);
}

void Enemy::SetDirection(sf::Vector2f dir)
{
	m_Direction = dir;
}

sf::Vector2f  Enemy::GetPosition()
{
	return sprite.getPosition();
}

void Enemy::Draw(sf::RenderWindow& window)
{
	sprite.setRotation(orientation);
	window.draw(sprite);
}
void Enemy::seek(sf::Vector2f target)
{
	//Velocity = target.position - my.position
	sf::Vector2f vel = target - m_Position;
	//Velocity = normalize(velocity)
	vel = VectorMath::GetInstance()->Normalise(vel);
	//Velocity = velocity * maxSpeed
	//Orientation = getNewOrientation(orientation, velocity)
	angleBetween = VectorMath::GetInstance()->GetAngleBetween(m_Direction, vel);

}

void Enemy::Rotate(float time)
{
	//cout << angleBetween << endl;
	if (angleBetween > 0)
	{
		orientation += rotationSpeed * time;
	}
	else if (angleBetween < 0)
	{
		orientation -= rotationSpeed * time;
	}
	m_Direction = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(orientation)), sin(VectorMath::GetInstance()->ToRadian(orientation))));
}