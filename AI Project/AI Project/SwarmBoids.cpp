
#include "SwarmBoids.h"

#include "BulletManager.h"
#include "EnemyManager.h"

SwarmBoids::SwarmBoids(sf::Texture* texture, sf::Vector2f pos, float width, float height)
{
	sf::Vector2u size = texture->getSize();
	m_Radius = (sqrt((size.x* size.x) + (size.y * size.y))) / 2;
	sprite.setTexture(*texture);
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	maxSpeed = 300;
	speed = 300;
	orientation = 0;
	angleBetween = 0;
	m_acceleration = 0;
	rotationSpeed = 150;
	m_Direction = sf::Vector2f(1, 0);
	m_Position = pos;
	sprite.setPosition(m_Position);
	attackRange = 400;
	noOfHits = 0;
	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	location = Pvector(pos.x, pos.y);
	//maxSpeed = 3.5;
	maxForce = 0.5;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	timeSinceCreatedShip = 0;
	createDelay = rand() % 20 + 10;
	canCreateShip = true;
	timeSinceLastFire = 0;
	fireDelay = 1;
	canfire = true;
}

void SwarmBoids::Init(sf::Texture* texture, sf::Vector2f pos)
{


}


void SwarmBoids::intercept(sf::Vector2f target, sf::Vector2f playerDirection, float playerSpeed)
{
	//direction = target.position - my.position
	sf::Vector2f direction = target - m_Position;
	//distance = direction.length
	float distance = VectorMath::GetInstance()->GetLength(direction);
	//speed = my.velocity.length
	//if speed <= distance / maxTimePrediction:
	float timePrediction = 0;

	//timePrediction = distance / speed
	timePrediction = distance / speed;

	//newtarget.position = target.position + target.velocity * timePrediction
	sf::Vector2f newTarget = target + playerDirection * playerSpeed * timePrediction;
	//seek(newTarget)
	seek(newTarget);
}

void SwarmBoids::Update(float time, Player* p, list<SwarmBoids*>* v)
{
	if (VectorMath::GetInstance()->getDistanceBetween(m_Position, p->GetPosition()) < attackRange)
	{
		intercept(p->GetPosition(), p->getDirection(), p->getSpeed());
		Rotate(time);
		move(time);
	}
	else
	{
		location = Pvector(m_Position.x, m_Position.y);
		Swarm(v, p->getPosition());
		updateSwarm(time);
		m_Position = sf::Vector2f(location.x, location.y);
		orientation = angle(velocity) - 90;
		//createPredator(time);
	}

	

	//Checks collision with the player.
	if (IsCollidingWithPlayer(p))
	{
		noOfHits++;
	}

	KeepInBounds();
	sprite.setPosition(m_Position);
}
void SwarmBoids::move(float time)
{
	m_Position += (m_Direction * speed  * time) + 0.5F * (m_acceleration * VectorMath::GetInstance()->Normalise(m_Direction)) * time * time;
}

void SwarmBoids::KeepInBounds()
{
	if (m_Position.x + 36 < -SCREEN_WIDTH - 36){ m_Position.x = SCREEN_WIDTH * 2 + 36; }
	else if (m_Position.x > SCREEN_WIDTH * 2 + 36){ m_Position.x = -SCREEN_WIDTH - 36; }
	if (m_Position.y < -SCREEN_HEIGHT){ m_Position.y = SCREEN_HEIGHT * 2; }
	else if (m_Position.y > SCREEN_HEIGHT * 2){ m_Position.y = -SCREEN_HEIGHT; }
}
void SwarmBoids::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	sprite.setPosition(m_Position);
}

void SwarmBoids::seek(sf::Vector2f target)
{
	//Velocity = target.position - my.position
	sf::Vector2f vel = target - m_Position;
	//Velocity = normalize(velocity)
	vel = VectorMath::GetInstance()->Normalise(vel);
	//Orientation = getNewOrientation(orientation, velocity)
	angleBetween = VectorMath::GetInstance()->GetAngleBetween(m_Direction, vel);

}

void SwarmBoids::SetDirection(sf::Vector2f dir)
{
	m_Direction = dir;
}

sf::Vector2f  SwarmBoids::GetPosition()
{
	return sprite.getPosition();
}

void SwarmBoids::Draw(sf::RenderWindow& window)
{
	sprite.setColor(sf::Color::White);
	sprite.setRotation(orientation);
	window.draw(sprite);
}
void SwarmBoids::Flee(sf::Vector2f target)
{
	//Velocity = target.position - my.position
	sf::Vector2f vel = target - m_Position;
	//Velocity = normalize(velocity)
	vel = VectorMath::GetInstance()->Normalise(vel);
	//Orientation = getNewOrientation(orientation, velocity)
	angleBetween = VectorMath::GetInstance()->GetAngleBetween(m_Direction, -vel);

}
void SwarmBoids::Rotate(float time)
{
	//cout << angleBetween << endl;
	if (angleBetween > 0)
	{
		orientation += rotationSpeed * time;
	}
	else if (angleBetween < 0)
	{
		orientation -= rotationSpeed * time;
	}
	m_Direction = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(orientation)), sin(VectorMath::GetInstance()->ToRadian(orientation))));
}

void SwarmBoids::Swarm(list<SwarmBoids*>* v, sf::Vector2f target)
{
	//Pvector sep = Separation(v);
	//Pvector ali = Alignment(v);
	//// Arbitrarily weight these forces
	//sep.mulScalar(1.5);
	//ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	////coh.mulScalar(1.0);
	//// Add the force vectors to acceleration
	//applyForce(sep);
	//applyForce(ali);
	////applyForce(coh);



	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/
	Pvector	R;
	Pvector sum(0, 0);
	float A = 100, B = 5000, N = 1, M = 2;
	Pvector t(target.x,target.y);
	

	// Your code here..
	for each(SwarmBoids* f in *v)
	{
		if (f != this)
		{
			R.set(R.subTwoVector(location, f->location));
			float D = R.magnitude();
			float U = -A / pow(D, N) + B / pow(D, M);
			R.normalize();
			R.mulScalar(U);
			sum.addVector(R);
		}
	}
	// have swarm tend towards player by adding its positon as part of the swarm 
	R.set(R.subTwoVector(location, t));
	float D = R.magnitude();
	float U = -A / pow(D, N) + B / pow(D, M);
	R.normalize();
	R.mulScalar(U);
	sum.addVector(R);

	sum.divScalar(v->size() );
	sum.normalize();
	applyForce(sum);
}


void SwarmBoids::applyForce(Pvector force)
{
	acceleration.addVector(force);
}
// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector SwarmBoids::Separation(list<SwarmBoids*>* v)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 105;

	Pvector steer(0, 0);
	int count = 0;
	// For every factory in the system, check if it's too close
	for each(SwarmBoids* f in *v)
	{
		float d = location.distance(f->location);
		if ((d > 0) && (d < desiredseparation))
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, f->location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}

	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}
// Alignment calculates the average velocity in the field of view and 
// manipulates the velocity of the Boid passed as parameter to adjust to that
// of nearby factories.
Pvector SwarmBoids::Alignment(list<SwarmBoids*>* v)
{
	float neighbordist = 200;

	Pvector sum(0, 0);
	int count = 0;
	for each(SwarmBoids* f in *v)
	{
		float d = location.distance(f->location);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum.addVector(f->velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
		// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)  
		steer.limit(maxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

//updateflocking modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void SwarmBoids::updateSwarm(float time)
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.4);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed * time);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

float SwarmBoids::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

bool SwarmBoids::IsCollidingWithPlayer(Player* p)
{
	
	if (sprite.getGlobalBounds().intersects(p->GetRectangle().getGlobalBounds()))
	{
		std::cout << "Swarm hit the player" << endl;
		p->PlayerLoseHealth();
		return true;
	}

	return false;
}


bool SwarmBoids::IsColiding(sf::Vector2f pos, float rad)
{
	if (VectorMath::GetInstance()->getDistanceBetween(pos, m_Position)< rad + m_Radius)
	{
		noOfHits++;
		return true;
	}
	return false;
}

bool SwarmBoids::IsAlive()
{
	if (noOfHits >= 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}