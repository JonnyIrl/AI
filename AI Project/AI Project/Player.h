#ifndef PLAYER
#define PLAYER

#include "Common.h"
#include "vectorMath.h"
#include "Camera.h"
#include "MiniMap.h"
#include "BulletManager.h"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
using namespace std;


class Player
{

public:
	Player(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Update(float time, sf::Time animationTime);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);

	//Animation method
	void updateTex(sf::Texture texture);
	void PlayDecellerationAnimation(sf::Time animationTime);
	bool LoadTexture();

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float speed, max_Speed, accelertation, accerationRate; // measure in pixels per second 
	float friction;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Position;
	float m_Radius;
	float rotation;
	void Rotate(int dir,float time);
	float rotationSpeed; // is measured in degrees per second
	void KeepInBounds();
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//Animation values
	Animation m_pMoveAnimation;
	Animation m_pStopMoveAnimation;
	AnimatedSprite m_playerAnimation;
	std::size_t lastframe, firstFrame;
	bool m_upPressedOnce;
	bool playerDecelleration;
};
//public vector m_Direction;



#endif 
