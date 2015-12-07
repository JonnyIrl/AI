#include "Player.h"



Player::Player(int WIDTH, int HEIGHT)
{
	if (!texture.loadFromFile("Assets/jet1.png"))
	{

	}
	sprite.setTexture(texture);
	sprite.setOrigin(35.5f, 20);

	speed = 200;
	rotation = 0;
	rotationSpeed = 90;
	m_Direction = sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(rotation)), sin(VectorMath::GetInstance()->ToRadian(rotation)));
	SCREEN_WIDTH = WIDTH;
	SCREEN_HEIGHT = HEIGHT;
}
void Player::Update(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		Rotate(-1, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		Rotate(1, time);
	}


	m_Position += m_Direction * speed * time;
	//KeepInBounds();
	sprite.setPosition(m_Position);
	Camera::GetInstance()->setViewPosition(m_Position);
	MiniMap::GetInstance()->setViewPosition(m_Position);

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

void Player::Rotate(int dir, float time)
{
	rotation += rotationSpeed*dir * time;
	m_Direction = sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(rotation)), sin(VectorMath::GetInstance()->ToRadian(rotation)));

}
void Player::KeepInBounds()
{
	if (m_Position.x + 36 < 0){ m_Position.x = SCREEN_WIDTH + 36; }
	else if (m_Position.x > SCREEN_WIDTH + 36){ m_Position.x = -36; }
	if (m_Position.y + 36 < 0){ m_Position.y = SCREEN_HEIGHT +36; }
	else if (m_Position.y > SCREEN_HEIGHT + 36){ m_Position.y = -36; }
}
