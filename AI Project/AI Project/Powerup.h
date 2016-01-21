#ifndef _POWERUP_H
#define _POWERUP_H_

#include "Common.h"
#include "Player.h"
#include <list>
using namespace std;

class Powerup
{
public:
	Powerup();
	~Powerup();
	void Update();

	Powerup(sf::Texture* texture, sf::Vector2f pos, float width, float height, bool isHealth, bool isSpeed, bool isShield);
	void Init(sf::Texture* texture, sf::Vector2f pos);
	void Update(float time, Player* p, list<Powerup*>* v);
	void SetPosition(sf::Vector2f pos);
	void SetDirection(sf::Vector2f dir);
	sf::Vector2f  GetPosition();
	void Draw(sf::RenderWindow& window);
	bool IsAlive();
	sf::Sprite GetSprite(){ return sprite; }
	bool IsCollidingWithPlayer(Player* p);


	bool playerHealth, playerShield;
	bool playerPowerSpeedUpActive;
	bool enemeyPowerSpeedUpActive;

private:
	//position
	//variables
	sf::Vector2f m_Position;// posiiton of enemy 
	float m_Radius; // radius of the object for colision detection
	float activeTime; //Amount of time the powerup stays active for.
	//methods
	int noOfHits;
	float SCREEN_WIDTH, SCREEN_HEIGHT;

	//for drawing sprite
	sf::Texture texture; //holds the sprites texture 
	sf::Sprite sprite; //holds the sprite

};


#endif
