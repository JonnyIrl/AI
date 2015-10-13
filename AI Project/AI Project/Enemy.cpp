#include "Enemy.h"


Enemy::Enemy()
{
	if (!texture.loadFromFile("jet2.png"))
	{

	}
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(35.5f, 20));
	maxSpeed = 50;
	speed = 100;
	orientation = 0;
	newOrientation = orientation;
	acceleration = 0;
	rotationSpeed = 2;
	m_Direction = sf::Vector2f(1, 0);
}
void Enemy::Update(float time, sf::Vector2f target)
{
	seek(target);
	Rotate();
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
	if (m_Position.x + 36 < 0){ m_Position.x = 800; }
	else if (m_Position.x > 800){ m_Position.x = -36; }
	if (m_Position.y + 20 < 0){ m_Position.y = 600; }
	else if (m_Position.y > 600){ m_Position.y = -20; }
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
	newOrientation = getNewOrientation(vel);

}
float Enemy::getNewOrientation(sf::Vector2f vec)
{
	float angle = atan2f(vec.y, vec.x) * 180 / 3.14;
	//angle = (int)angle % 360;
	return angle;
}
void Enemy::Rotate()
{



	if (newOrientation < orientation)
	{
		float angleBetween = newOrientation - orientation;
		if (angleBetween < -180)
		{
			orientation += rotationSpeed;
		}
		else
		{
			orientation -= rotationSpeed;
		}
	}
	else if (newOrientation > orientation)
	{
		float angleBetween = newOrientation - orientation;
		if (angleBetween < -180)
		{
			orientation -= rotationSpeed;
		}
		else
		{
			orientation += rotationSpeed;
		}

	}
	if (orientation > 180)
	{
		orientation = -180 + ((int)orientation % 180);
	}
	if (orientation < -180)
	{
		orientation = 180 + ((int)orientation % 180);
	}

	m_Direction = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(orientation)), sin(VectorMath::GetInstance()->ToRadian(orientation))));
}