#include "FactoryShip.h"


FactoryShip::FactoryShip(sf::Texture* texture, sf::Vector2f pos, float width,float height)
{
	sf::Vector2u size = texture->getSize();
	m_Radius = (sqrt((size.x* size.x) + (size.y * size.y))) / 2;
	sprite.setTexture(*texture);
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	maxSpeed = 200;
	speed = 200;
	orientation = 0;
	angleBetween = 0;
	m_acceleration = 0;
	rotationSpeed = 50;
	m_Direction = sf::Vector2f(1, 0);
	m_Position = pos;
	sprite.setPosition(m_Position);
	fleeRange = 300;

	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	location = Pvector(pos.x, pos.y);
	//maxSpeed = 3.5;
	maxForce = 0.5;
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	timeSinceCreatedShip = 0;
	createDelay = 5;
	canCreateShip = true;
}

void FactoryShip::Init(sf::Texture* texture, sf::Vector2f pos)
{


}

void FactoryShip::Update(float time, Player* p, list<FactoryShip*>* v)
{
	if (VectorMath::GetInstance()->getDistanceBetween(m_Position, p->GetPosition()) < fleeRange)
	{
		Flee(p->GetPosition());
		Rotate(time);
		move(time);
	}
	else
	{
		location = Pvector(m_Position.x, m_Position.y);
		flock(v);
		updateflocking(time);
		m_Position = sf::Vector2f(location.x, location.y);
		orientation = angle(velocity) - 90;
		createPredator(time);
	}
	KeepInBounds();
	sprite.setPosition(m_Position);
}
void FactoryShip::move(float time)
{
	m_Position += (m_Direction * speed  * time) + 0.5F * (m_acceleration * VectorMath::GetInstance()->Normalise(m_Direction)) * time * time;
}

void FactoryShip::KeepInBounds()
{
	if (m_Position.x + 36 < -SCREEN_WIDTH - 36){ m_Position.x = SCREEN_WIDTH * 2 + 36; }
	else if (m_Position.x > SCREEN_WIDTH * 2 + 36){ m_Position.x = -SCREEN_WIDTH - 36; }
	if (m_Position.y < -SCREEN_HEIGHT){ m_Position.y = SCREEN_HEIGHT * 2; }
	else if (m_Position.y > SCREEN_HEIGHT * 2){ m_Position.y = -SCREEN_HEIGHT; }
}
void FactoryShip::SetPosition(sf::Vector2f pos)
{
	m_Position = pos;
	sprite.setPosition(m_Position);
}

void FactoryShip::SetDirection(sf::Vector2f dir)
{
	m_Direction = dir;
}

sf::Vector2f  FactoryShip::GetPosition()
{
	return sprite.getPosition();
}

void FactoryShip::Draw(sf::RenderWindow& window)
{
	sprite.setColor(sf::Color::Red);
	sprite.setRotation(orientation);
	window.draw(sprite);
}
void FactoryShip::Flee(sf::Vector2f target)
{
	//Velocity = target.position - my.position
	sf::Vector2f vel = target - m_Position;
	//Velocity = normalize(velocity)
	vel = VectorMath::GetInstance()->Normalise(vel);
	//Orientation = getNewOrientation(orientation, velocity)
	angleBetween = VectorMath::GetInstance()->GetAngleBetween(m_Direction, -vel);

}
void FactoryShip::Rotate(float time)
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

void FactoryShip::flock(list<FactoryShip*>* v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void FactoryShip::applyForce(Pvector force)
{
	acceleration.addVector(force);
}
// Function that checks and modifies the distance
// of a boid if it breaks the law of separation.
Pvector FactoryShip::Separation(list<FactoryShip*>* v)
{
	// If the boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between boids
	float desiredseparation = 105;

	Pvector steer(0, 0);
	int count = 0;
	// For every factory in the system, check if it's too close
	for each(FactoryShip* f in *v)
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
Pvector FactoryShip::Alignment(list<FactoryShip*>* v)
{
	float neighbordist = 200;

	Pvector sum(0, 0);
	int count = 0;
	for each(FactoryShip* f in *v)
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
// Cohesion finds the average location of nearby factories and manipulates the 
// steering force to move in that direction.
Pvector FactoryShip::Cohesion(list<FactoryShip*>* v)
{
	float neighbordist = 200;

	Pvector sum(0, 0);
	int count = 0;
	for each(FactoryShip* f in *v)
	{
		float d = location.distance(f->location);
		if ((d > 0) && (d < neighbordist))
		{
			sum.addVector(f->location);
			count++;
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}
// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Pvector FactoryShip::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}
//updateflocking modifies velocity, location, and resets acceleration with values that
//are given by the three laws.
void FactoryShip::updateflocking(float time)
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

float FactoryShip::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

/*creates a new predator ship*/
void FactoryShip::createPredator(float time)
{
	if (canCreateShip)
	{
		EnemyManager::GetInstance()->AddPredator(m_Position);
		canCreateShip = false;
		timeSinceCreatedShip = 0;
	}
	else
	{
		timeSinceCreatedShip += time;
		if (timeSinceCreatedShip >= createDelay)
		{
			canCreateShip = true;
		}
	}
}