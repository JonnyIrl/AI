#ifndef OBJECT
#define OBJECT
#include "Common.h"
#include "vectorMath.h"

using namespace std;


class Enemy
{

public:
	Enemy();
	void Update(float time, sf::Vector2f target);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);


private:
	//position
	//variables
	sf::Vector2f m_Position;
	//methods


	//moving
	//variables
	sf::Vector2f m_Direction;
	float maxSpeed;
	float speed;
	float acceleration;
	//methods
	void move(float time);
	void KeepInBounds();
	void seek(sf::Vector2f target);

	//rotating
	//variables
	float m_Radius;
	float orientation;
	float newOrientation;
	float rotationSpeed;
	//methods
	float getNewOrientation(sf::Vector2f velocity);
	void Rotate();

	//for drawing sprite
	sf::Texture texture;
	sf::Sprite sprite;



};
//public vector m_Direction;



#endif 
