#include "Player.h"


Player::Player()
{
	m_vel = sf::Vector2f(0, 0);
	m_box.setSize(sf::Vector2f(32, 32));
	m_alive = true;
	rotating = false;
	angle = 0.0f;
	jump_speed = 420.0f;
	jump_wpn_speed = 100.0f;
	move_speed = 0.0f;
	rotationSpeed = 240.0f;
	recoverySpeed = 450.0f;
	grav = 1.4f;
	m_box.setOrigin(16, 16);
	deltaTime = 0.0f;
	colliding = false;
	rock, paper, scissors = false;
	colourchange = false;
	jumpingSound = false;
	flyingSound = false;
	ifFlying = false;
	playJumpingSound = true;
	mainGameSound = true;
	currentSide = "blade";
	sideSwitch = false;
	switchSpeed = 0;
	targetRotation = 0;
	poweredUp = false;
	powerCount = 0;
	isVisible = true;
	rotSpeed1 = 400;
	rotSpeed2 = 800;
	rotSpeed3 = 1200;
}


void Player::updateTex(sf::Texture texture, sf::Texture texture2)
{ //creates a copy of your texture you pass

	m_box.setTexture(&texture); //actually takes the address of your texture 
}

void Player::Update()
{

	timeSinceLastUpdate = clock.getElapsedTime();
	deltaTime = timeSinceLastUpdate.asSeconds();
	clock.restart();


	if (powerCount >= 3)
	{
		poweredUp = true;
		powerCount = 0;

	}

	if (poweredUp)
	{
		powerCount += timeSinceLastUpdate.asSeconds();
		move_speed = 800;
		angle = 270;
		m_pos.y = 300;
		colliding = false;

		if (powerCount >= 1.0f)
			poweredUp = false;
	}

	if (!poweredUp)
	{
		move_speed = 250;
	}


	//Moving the player right.
	m_vel.x = move_speed;// * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && colliding == true && sideSwitch == false)
	{
		rotating = true;
		m_pos.y -= 10;
		m_vel.y = -jump_speed;
		colliding = false;
		if (playJumpingSound)
			jumpingSound = true;

	}
	else
		jumpingSound = false;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (playJumpingSound)
		{
			playJumpingSound = false;
		}

		else if (playJumpingSound == false)
		{
			playJumpingSound = true;
		}
	}

	//Moved all that big long horrible looking code into a method.
	SeperateUpdate();

	m_pos += m_vel * deltaTime;
	//cout << "X:" << m_vel.x << " Y:" << m_vel.y << endl;
	//ANGLE 0 = BLADE
	cout << "Angle = " << angle << endl;
	m_box.setPosition(m_pos);

}

void Player::SeperateUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && colliding == true && sideSwitch == false)
	{
		//blade side (angle = 0)
		m_pos.y -= 10;
		m_vel.y = -jump_wpn_speed;
		colliding = false;
		if (playJumpingSound)
			jumpingSound = true;

		if (currentSide == "blade"){
			//don't rotate
		}
		else if (currentSide == "sideBottom"){
			sideSwitch = true;
			switchSpeed = rotSpeed1;
			currentSide = "blade";
		}
		if (currentSide == "sideLeft"){
			sideSwitch = true;
			switchSpeed = rotSpeed2;
			currentSide = "blade";
		}
		else if (currentSide == "spikes"){
			sideSwitch = true;
			switchSpeed = rotSpeed3;
			currentSide = "blade";
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && colliding == true && sideSwitch == false)
	{
		//spikes side (angle = 90)
		m_pos.y -= 10;
		m_vel.y = -jump_wpn_speed;
		colliding = false;
		if (playJumpingSound)
			jumpingSound = true;
		if (currentSide == "spikes"){
			//don't rotate
		}
		else if (currentSide == "blade"){
			sideSwitch = true;
			switchSpeed = rotSpeed1;
			currentSide = "spikes";
		}
		if (currentSide == "sideBottom"){
			sideSwitch = true;
			switchSpeed = rotSpeed2;
			currentSide = "spikes";
		}
		else if (currentSide == "sideLeft"){
			sideSwitch = true;
			switchSpeed = rotSpeed3;
			currentSide = "spikes";
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && colliding == true && sideSwitch == false)
	{
		//sideLeft (angle = 180)
		m_pos.y -= 10;
		m_vel.y = -jump_wpn_speed;
		colliding = false;
		if (playJumpingSound)
			jumpingSound = true;

		if (currentSide == "sideLeft"){
			//don't rotate
		}
		else if (currentSide == "spikes"){
			sideSwitch = true;
			switchSpeed = rotSpeed1;
			currentSide = "sideLeft";
		}
		if (currentSide == "blade"){
			sideSwitch = true;
			switchSpeed = rotSpeed2;
			currentSide = "sideLeft";
		}
		else if (currentSide == "sideBottom"){
			sideSwitch = true;
			switchSpeed = rotSpeed3;
			currentSide = "sideLeft";
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && colliding == true && sideSwitch == false)
	{
		//sideBottom (angle = 270)
		m_pos.y -= 10;
		m_vel.y = -jump_wpn_speed;
		colliding = false;
		if (playJumpingSound)
			jumpingSound = true;

		if (currentSide == "sideBottom"){
			//don't rotate
		}
		else if (currentSide == "sideLeft"){
			sideSwitch = true;
			switchSpeed = rotSpeed1;
			currentSide = "sideBottom";
		}
		if (currentSide == "spikes"){
			sideSwitch = true;
			switchSpeed = rotSpeed2;
			currentSide = "sideBottom";
		}
		else if (currentSide == "blade"){
			sideSwitch = true;
			switchSpeed = rotSpeed3;
			currentSide = "sideBottom";
		}
	}



	if (!colliding)
	{
		m_vel.y += grav;// * deltaTime;
	}
	else
	{
		m_vel.y = 0;
		//m_vel.x = move_speed * deltaTime;
		//the following makes the cube able to land on any side
		//it checks between angles of 45 of each face(which are at multiples of 90) to determine whether to rotate backward or forward to get to the nearest face.
		if (angle > 0 && angle < 45){
			angle -= (recoverySpeed + rotationSpeed) * deltaTime; //adding rotationSpeed counteracts the actual rotation speed of the object
			if (angle <= 0){
				rotating = false;
				sideSwitch = false;
				currentSide = "blade";
				m_box.setRotation(0);
				angle = 0;
			}
		}
		else if (angle > 45 && angle < 90){
			angle += (recoverySpeed)* deltaTime; //rotationSpeed doesn't need to be added as its rotating in the positive direction
			if (angle >= 90){
				rotating = false;
				sideSwitch = false;
				currentSide = "spikes";
				m_box.setRotation(90);
				angle = 90;
			}
		}
		if (angle > 90 && angle < 135){
			angle -= (recoverySpeed + rotationSpeed) * deltaTime;
			if (angle <= 90){
				rotating = false;
				sideSwitch = false;
				currentSide = "spikes";
				m_box.setRotation(90);
				angle = 90;
			}
		}
		else if (angle > 135 && angle < 180){
			angle += (recoverySpeed)* deltaTime;
			if (angle >= 180){
				rotating = false;
				sideSwitch = false;
				currentSide = "sideLeft";
				m_box.setRotation(180);
				angle = 180;
			}
		}
		if (angle > 180 && angle < 225){
			angle -= (recoverySpeed + rotationSpeed) * deltaTime;
			if (angle <= 180){
				rotating = false;
				sideSwitch = false;
				currentSide = "sideLeft";
				m_box.setRotation(180);
				angle = 180;
			}
		}
		else if (angle > 225 && angle < 270){
			angle += (recoverySpeed)* deltaTime;
			if (angle >= 270){
				rotating = false;
				sideSwitch = false;
				currentSide = "sideBottom";
				m_box.setRotation(270);
				angle = 270;
			}
		}
		if (angle > 270 && angle < 315){
			angle -= (recoverySpeed + rotationSpeed) * deltaTime;
			if (angle <= 270){
				rotating = false;
				sideSwitch = false;
				currentSide = "sideBottom";
				m_box.setRotation(270);
				angle = 270;
			}
		}
		else if (angle > 315 && angle < 360){
			angle += (recoverySpeed)* deltaTime;
			if (angle >= 360){
				rotating = false;
				sideSwitch = false;
				currentSide = "blade";
				m_box.setRotation(0);
				angle = 0;
			}
		}
	}

	if (rotating)
	{
		angle += rotationSpeed * deltaTime;
		m_box.setRotation(angle);

		if (angle >= 360)
			angle = 0;
	}
	else
	{
		m_box.setRotation(angle);
	}
	if (sideSwitch)
	{

		angle += switchSpeed * deltaTime;
		m_box.setRotation(angle);

		if (angle >= 360)
			angle = 0;
	}
	else
	{
		m_box.setRotation(angle);
	}
}

void Player::Draw(sf::RenderWindow &window)
{
	if (isVisible)
	{
		window.draw(m_box);
	}
}

//getters and setters
//position
void Player::setPosition(sf::Vector2f newPos)
{
	m_pos = newPos;
}
sf::Vector2f Player::getPosition()
{
	return m_pos;
}
//velocity
void Player::setVelocity(sf::Vector2f newVel)
{
	m_vel = newVel;
}
sf::Vector2f Player::getVelocity()
{
	return m_vel;
}
//alive
void Player::setAlive(bool alive)
{
	m_alive = alive;
}
bool Player::getAlive()
{
	return m_alive;
}
//alive
void Player::setIfFlying(bool flying)
{
	ifFlying = flying;
}
bool Player::getIfFlying()
{
	return ifFlying;
}
//name
void Player::setName(string name)
{
	m_name = name;
}
string Player::getName()
{
	return m_name;
}
//score
void Player::setScore(int score)
{
	m_score = score;
}
int Player::getScore()
{
	return m_score;
}
//shape
sf::RectangleShape Player::getShape()
{
	return m_box;
}
//angle
double Player::getAngle(){
	return angle;
}
void Player::setAngle(double pAngle){
	angle = pAngle;
}
