#include <iostream>
#ifndef _PLAYER
#define _PLAYER

using namespace std;

class Player
{
public:
	Player();
	void Update();
	void Draw(sf::RenderWindow& window);
	bool move;
	//get and set methods
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f);
	sf::Vector2f getVelocity();
	void setAlive(bool);
	bool getAlive();
	void setIfFlying(bool);
	bool getIfFlying();
	void setName(string);
	string getName();
	void setScore(int);
	int getScore();
	sf::RectangleShape getShape();
	double getAngle();
	void setAngle(double);
	//end get and set

	void SeperateUpdate();
	void updateTex(sf::Texture, sf::Texture);
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	//sf::Vector2f gravity
	sf::RectangleShape m_box;
	double angle;
	float rotationSpeed;
	float recoverySpeed;
	bool colliding;
	bool rotating;

	float jump_speed;
	float jump_wpn_speed;
	float move_speed;
	sf::Time timeSinceLastUpdate;
	float deltaTime;

	float grav;
	sf::Clock clock;
	//PLAYER WEAPONS
	bool rock, paper, scissors;
	bool colourchange;
	bool jumpingSound;
	bool playJumpingSound;
	bool flyingSound;
	bool ifFlying;
	bool mainGameSound;

	bool sideSwitch;
	float switchSpeed;
	string currentSide;
	float targetRotation;

	bool poweredUp;
	float powerCount;
	bool isVisible;
	int rotSpeed1;
	int rotSpeed2;
	int rotSpeed3;
protected:

	sf::Sprite m_spr;
	bool m_alive;
	bool m_gravity;
	string m_name;
	int m_score;
};

#endif 