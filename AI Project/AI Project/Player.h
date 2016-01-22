#ifndef _PLAYER_H
#define _PLAYER_H

#include "Common.h"
#include "vectorMath.h"
#include "Camera.h"
#include "HUD.h"
#include "MiniMap.h"

#include "Animation.hpp"
#include "AnimatedSprite.hpp"
using namespace std;

class Player
{

public:
	Player(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool Update(float time, sf::Time animationTime);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	sf::RectangleShape GetRectangle();
	void Draw(sf::RenderWindow& window);
	void CheckHealth();
	void CheckShield();
	void PlayerLoseHealth();
	void PlayerIncreaseHealth();
	void PlayerIncreaseShield();

	//Animation method
	void updateTex(sf::Texture texture);
	void PlayDecellerationAnimation(sf::Time animationTime);
	bool LoadTexture();
	float timeSinceFire, fireDelay;
	bool readyToFire;
	sf::Vector2f getDirection(){ return m_Direction; }
	sf::Vector2f getPosition(){ return m_Position; }
	float getSpeed(){ return speed; }
	float GetRadius(){ return m_Radius; }
	sf::Sprite GetSprite(){ return sprite; }
	bool isColliding(sf::Vector2f position, float radius);
	void RestartClock();
	sf::RectangleShape PlayerHealthHUD(){ return healthRectangle; }
	sf::RectangleShape PlayerShieldHUD(){ return shieldRectangle; }
	bool Alive(){ return alive; }

private:
	sf::Texture texture;
	sf::Texture healthTexture;
	sf::Texture shieldTexture;
	sf::Sprite sprite;
	sf::RectangleShape playerRect;
	sf::RectangleShape healthRectangle;
	sf::RectangleShape shieldRectangle;

	float speed, max_Speed, accelertation, accerationRate; // measure in pixels per second 
	float friction;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Position;
	float m_Radius;
	float rotation;
	void Rotate(int dir, float time);
	float rotationSpeed; // is measured in degrees per second
	void KeepInBounds();
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int noOfHits;
	//Animation values
	Animation m_pMoveAnimation;
	Animation m_pStopMoveAnimation;
	AnimatedSprite m_playerAnimation;
	std::size_t lastframe, firstFrame;
	bool m_upPressedOnce;
	bool playerDecelleration;

	float bulletSpeed;
	sf::Clock speedClock;
	float speedTimer;
	bool speedPowerUpActive, healthPowerUpActive, shieldPowerUpActive;
	bool alive;
	int shieldHealth;
	int playerHealth;
};
//public vector m_Direction;
#endif 
