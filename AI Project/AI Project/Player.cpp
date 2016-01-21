#include "Player.h"
#include "BulletManager.h"


Player::Player(int WIDTH, int HEIGHT)
{
	//Set up the animations.
	if (LoadTexture())
	{
		m_pMoveAnimation.setSpriteSheet(texture);
		m_pMoveAnimation.addFrame(sf::IntRect(0, 0, 71, 40));
		m_pMoveAnimation.addFrame(sf::IntRect(142, 0, 71, 40));
		m_pMoveAnimation.addFrame(sf::IntRect(213, 0, 71, 40));

		m_pStopMoveAnimation.setSpriteSheet(texture);
		m_pStopMoveAnimation.addFrame(sf::IntRect(213, 0, 71, 40));
		m_pStopMoveAnimation.addFrame(sf::IntRect(142, 0, 71, 40));
		m_pStopMoveAnimation.addFrame(sf::IntRect(0, 0, 71, 40));
			

		m_playerAnimation = AnimatedSprite(sf::seconds(0.15f));
		m_playerAnimation.setAnimation(m_pMoveAnimation);
		lastframe = 2;
		firstFrame = 0;
		m_upPressedOnce = false;
		playerDecelleration = true;

		speedPowerUpActive = false;
		healthPowerUpActive = false;
		shieldPowerUpActive = false;

		playerRect.setSize(sf::Vector2f(50, 40));
		playerRect.setOrigin(sf::Vector2f(25, 20));

		healthRectangle.setSize(sf::Vector2f(200, 50));
		healthRectangle.setTexture(&healthTexture);
		healthRectangle.setPosition(sf::Vector2f(0, 0));
		healthRectangle.setTextureRect(sf::IntRect(1800, 0, 200, 50));

	}

	sprite.setTexture(texture);
	sprite.setOrigin(35.5f, 20);
	m_playerAnimation.setOrigin(sf::Vector2f(35.5, 20));
	speed = 0;
	accerationRate = 100;
	accelertation = 0;
	max_Speed = 300;
	friction = -10;
	rotation = 0;
	rotationSpeed = 90;
	m_Direction = sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(rotation)), sin(VectorMath::GetInstance()->ToRadian(rotation)));
	SCREEN_WIDTH = WIDTH;
	SCREEN_HEIGHT = HEIGHT;
	timeSinceFire = 0;
	fireDelay = 0.25f;
	readyToFire = true;
	noOfHits = 0;
	m_Radius = texture.getSize().y/2;
	bulletSpeed = 900;
	//speedPowerUpTime = 0;
}

sf::RectangleShape Player::GetRectangle()
{
	return playerRect; 
}

bool Player::LoadTexture()
{
	if (!texture.loadFromFile("Assets/Player/playerSpriteSheet.png"))
		return false;

	if (!healthTexture.loadFromFile("Assets/Health/healthSpriteSheet.png"))
		return false;


	else
		return true;
}

void Player::CheckHealth()
{

}

void Player::Update(float time, sf::Time animationTime)
{
	accelertation = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// left key is pressed: move our character
		Rotate(-2, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// left key is pressed: move our character
		Rotate(2, time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_upPressedOnce)
			m_upPressedOnce = true;

		//If the player has the speed powerup
		if (speedPowerUpActive)
		{
			if (speed < max_Speed + 150)
			{
				accelertation = accerationRate + 50;
			}

			else
			{
				speed = max_Speed + 150;
			}

			if (m_playerAnimation.getAnimation() != &m_pMoveAnimation)
				m_playerAnimation.setAnimation(m_pMoveAnimation);
			//Used to keep the image on the last thruster update
			if (m_playerAnimation.m_currentFrame == lastframe)
			{
				m_playerAnimation.setFrame(lastframe);
				if (playerDecelleration)
					playerDecelleration = false;
			}

			else
			{
				m_playerAnimation.update(animationTime);
			}

		}

		else
		{

			if (speed < max_Speed)
			{
				accelertation = accerationRate;
			}
			else
			{
				speed = max_Speed;
			}

			if (m_playerAnimation.getAnimation() != &m_pMoveAnimation)
				m_playerAnimation.setAnimation(m_pMoveAnimation);
			//Used to keep the image on the last thruster update
			if (m_playerAnimation.m_currentFrame == lastframe)
			{
				m_playerAnimation.setFrame(lastframe);
				if (playerDecelleration)
					playerDecelleration = false;
			}

			else
			{
				m_playerAnimation.update(animationTime);
			}
		}
	}

	//Check for when the up key is not pressed then play the same animation but in reverse essentially.
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !playerDecelleration)
	{
		PlayDecellerationAnimation(animationTime);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > 0)
		{
			accelertation = -accerationRate;
		}
	}
	if (readyToFire)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (speedPowerUpActive)
			{
				BulletManager::GetInstance()->AddPlayerBullet(m_Position + m_Direction*35.0f, rotation, bulletSpeed + 800, 3);
				readyToFire = false;
				timeSinceFire = 0;
			}

			else
			{
				BulletManager::GetInstance()->AddPlayerBullet(m_Position + m_Direction*35.0f, rotation, bulletSpeed, 3);
				readyToFire = false;
				timeSinceFire = 0;
			}
		}
		
	}
	else 
	{
		timeSinceFire += time;
		if (timeSinceFire >= fireDelay)
		{
			readyToFire = true;
		}
	}
	


	m_Position += m_Direction * speed * time;
	KeepInBounds();
	//s=ut+(1/2)a(t(t))
	m_Position += m_Direction * speed * time + m_Direction * 0.5f* accelertation * time *time;
	//v=u+at
	speed += accelertation* time;
	if (speed > 0)
	{
		speed += friction* time;
	}
	//KeepInBounds();
	sprite.setPosition(m_Position);
	playerRect.setPosition(sf::Vector2f(m_Position.x, m_Position.y));
	playerRect.setRotation(rotation);
	m_playerAnimation.setPosition(m_Position);
	Camera::GetInstance()->setViewPosition(m_Position);
	//MiniMap::GetInstance()->setViewPosition(m_Position);


	//Checks for the powerups.
	if (speedPowerUpActive)
	{
		speedTimer = speedClock.getElapsedTime().asSeconds();

		if (speedTimer >= 10)
		{
			speedPowerUpActive = false;
		}
	}

}

void Player::RestartClock()
{
	speedClock.restart();
	speedTimer = 0;
	speedPowerUpActive = true;
}


void Player::PlayDecellerationAnimation(sf::Time animationTime)
{
	if (m_playerAnimation.getAnimation() != &m_pStopMoveAnimation)
		m_playerAnimation.setAnimation(m_pStopMoveAnimation);

	m_playerAnimation.update(animationTime);

	if (m_playerAnimation.m_currentFrame == lastframe)
	{
		playerDecelleration = true;
	}
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
	//sprite.setRotation(rotation);
	
	m_playerAnimation.setRotation(rotation);
	window.draw(healthRectangle);
	window.draw(m_playerAnimation);
	//window.draw(playerRect);
	//window.draw(sprite);
}

void Player::Rotate(int dir, float time)
{
	rotation += rotationSpeed*dir * time;
	m_Direction = sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(rotation)), sin(VectorMath::GetInstance()->ToRadian(rotation)));

}
void Player::KeepInBounds()
{
	if (m_Position.x + 36 < -SCREEN_WIDTH -36){ m_Position.x = SCREEN_WIDTH*2 + 36; }
	else if (m_Position.x > SCREEN_WIDTH * 2 + 36){ m_Position.x = -SCREEN_WIDTH - 36; }
	if (m_Position.y < -SCREEN_HEIGHT ){ m_Position.y = SCREEN_HEIGHT * 2 ; }
	else if (m_Position.y > SCREEN_HEIGHT * 2 ){ m_Position.y = -SCREEN_HEIGHT ; }
}
bool Player::isColliding(sf::Vector2f position, float radius)
{
	if (VectorMath::GetInstance()->getDistanceBetween(position, m_Position)< radius + m_Radius)
	{
		noOfHits++;
		return true;
	}
	return false;
}