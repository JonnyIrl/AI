#ifndef SWARMBOIDS_h
#define SWARMBOIDS_H
#include "Common.h"
#include "Pvector.h"
#include "vectorMath.h"
#include "Player.h"
#include <list>

using namespace std;
#define PI 3.141592635

class SwarmBoids
{

public:
	SwarmBoids(sf::Texture* texture, sf::Vector2f pos, float width, float height);
	~SwarmBoids()
	{
		cout << "Deleteing Swarm Boids Enemy" << endl;
	}
	void Init(sf::Texture* texture, sf::Vector2f pos);
	void Update(float time, Player* p, list<SwarmBoids*>* v);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);
	bool IsColiding(sf::Vector2f pos, float rad);
	Pvector location;
	Pvector velocity;
	Pvector acceleration;
	bool IsAlive();
	sf::Sprite GetSprite(){ return sprite; }
	void intercept(sf::Vector2f playerPos, sf::Vector2f direction, float speed);
	bool IsCollidingWithPlayer(Player* p);
private:
	//position
	//variables
	sf::Vector2f m_Position;// posiiton of enemy 
	float m_Radius; // radius of the object for colision detection
	float attackRange;
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

	void Swarm(list<SwarmBoids*>* v, sf::Vector2f target);

	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(list<SwarmBoids*>* v);
	Pvector Alignment(list<SwarmBoids*>* v);

	void updateSwarm(float time);

	void seek(sf::Vector2f v);

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
