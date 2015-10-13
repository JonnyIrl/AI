#include "Player.h"



Player::Player()
{
	if (!texture.loadFromFile("jet1.png"))
	{

	}
	sprite.setTexture(texture);
	sprite.setOrigin(35.5f, 20);

	speed = 200;
	rotation = 0;
	rotationSpeed = 2;
	m_Direction = sf::Vector2f(cos(ToRadian(rotation)), sin(ToRadian(rotation)));

}
void Player::Update(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		Rotate(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		Rotate(1);
	}


	m_Position += m_Direction * speed * time;
	KeepInBounds();
	sprite.setPosition(m_Position);

}
void Player::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	sprite.setPosition(m_Position);
}

void Player::SetDirection(sf::Vector2f dir)
{
	m_Direction = dir;
}

sf::Vector2f  Player::GetPosition()
{
	return sprite.getPosition();
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setRotation(rotation);
	window.draw(sprite);
}

void Player::Rotate(int dir)
{
	rotation += rotationSpeed*dir;
	m_Direction = sf::Vector2f(cos(ToRadian(rotation)), sin(ToRadian(rotation)));

}
float Player::ToRadian(float deg)
{
	return (deg*3.14) / 180;
}
void Player::KeepInBounds()
{
	if (m_Position.x + 36 < 0){ m_Position.x = 800 + 36; }
	else if (m_Position.x > 836){ m_Position.x = -36; }
	if (m_Position.y + 36 < 0){ m_Position.y = 600 +36; }
	else if (m_Position.y > 636){ m_Position.y = -36; }
}
