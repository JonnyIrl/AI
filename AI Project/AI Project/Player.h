#ifndef PLAYER
#define PLAYER

#include "Common.h"
#include "vectorMath.h"
using namespace std;


class Player
{

public:
	Player();
	void Update(float time);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);


private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Position;
	float m_Radius;
	float rotation;
	void Rotate(int dir);
	float rotationSpeed;
	void KeepInBounds();


};
//public vector m_Direction;



#endif 
