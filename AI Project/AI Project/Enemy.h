#ifndef OBJECT
#define OBJECT
#include "Common.h"
#include "vectorMath.h"
#include "Player.h"

using namespace std;


class Enemy
{

public:
	Enemy(sf::Texture* texture, sf::Vector2f pos);
	~Enemy()
	{
		cout << "Deleteing Enemy" << endl;
	}
	void Init(sf::Texture* texture, sf::Vector2f pos);
	void Update(float time, Player* p);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);


private:
	//position
	//variables
	sf::Vector2f m_Position;// posiiton of enemy 
	float m_Radius; // radius of the object for colision detection
	//methods


	//moving
	//variables
	sf::Vector2f m_Direction;// direction of enemy as a normalised vector
	float maxSpeed;// measure in pixels per second 
	float speed;// measure in pixels per second 
	float acceleration; // measure in pixels per second squared 
	//methods
	void move(float time);
	void KeepInBounds();
	void seek(sf::Vector2f target);

	//rotating
	//variables
	
	float orientation;// which wAY currently facing measured in degress
	float angleBetween; // the angle betwswen the current direction and the direction vector to the target 
	float rotationSpeed;// is measured in degrees per second
	//methods
	void Rotate(float time);

	//for drawing sprite
	sf::Texture texture; //holds the sprites texture 
	sf::Sprite sprite; //holds the sprite



};
//public vector m_Direction;



#endif 
