#ifndef FACTORYSHIP_h
#define FACTORYSHIP_H
#include "Common.h"
#include "Pvector.h"
#include "vectorMath.h"
#include "Player.h"
#include <list>

using namespace std;
#define PI 3.141592635

class FactoryShip
{

public:
	FactoryShip(sf::Texture* texture, sf::Vector2f pos, float width, float height);
	~FactoryShip()
	{
		cout << "Deleteing Enemy" << endl;
	}
	void Init(sf::Texture* texture, sf::Vector2f pos);
	void Update(float time, Player* p, list<FactoryShip*>* v);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);
	bool IsColiding(sf::Vector2f pos, float rad);
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	bool IsAlive();
private:
	//position
	//variables
	sf::Vector2f m_Position;// posiiton of enemy 
	float m_Radius; // radius of the object for colision detection
	float fleeRange;
	//methods
	int noOfHits;
	float SCREEN_WIDTH, SCREEN_HEIGHT;

	//moving
	//variables
	sf::Vector2f m_Direction;// direction of enemy as a normalised vector
	//float m_maxSpeed;// measure in pixels per second 
	float speed;// measure in pixels per second 
	float m_acceleration; // measure in pixels per second squared 

	//methods
	void move(float time);
	void KeepInBounds();
	void Flee(sf::Vector2f target);

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

	void flock(list<FactoryShip*>* v);

	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(list<FactoryShip*>* v);
	Pvector Alignment(list<FactoryShip*>* v);
	Pvector Cohesion(list<FactoryShip*>* v);

	void updateflocking(float time);

	Pvector seek(Pvector v);

	float maxSpeed;
	float maxForce;

	float angle(Pvector v);

	void firePredatorMissile(float time, Player * p);
	void createPredator(float time);
	float timeSinceCreatedShip, createDelay, timeSinceLastFire, fireDelay;
	bool canCreateShip, canfire;
	 


};
//public vector m_Direction;



#endif 
