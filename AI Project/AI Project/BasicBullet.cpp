#include "BasicBullet.h"
#include "FactoryManager.h"
#include "vectorMath.h"

BasicBullet::BasicBullet(sf::Vector2f pos, float rotation, float speed, float timeToLive, sf::Texture* texture)
{
	//float m_speed, m_timeAlive, m_timeToLive, m_damage, m_rotation;
	//sf::Vector2f m_pos, m_dir;
	m_pos = pos;
	m_speed = speed;
	m_timeToLive = timeToLive;
	m_timeAlive = 0;
	m_sprite.setTexture(*texture);
	m_friction = -10;
	m_rotation = rotation;
	m_dir = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(m_rotation)), sin(VectorMath::GetInstance()->ToRadian(m_rotation))));
	sf::Vector2u size = texture->getSize();
	m_radius = size.x / 2;
	m_sprite.setOrigin(size.x/2,size.y/2);
	m_sprite.setRotation(m_rotation);
	m_sprite.setPosition(m_pos);
}
BasicBullet::BasicBullet(sf::Vector2f pos, float speed, float timeToLive, sf::Texture* texture,Player* target)
{
	//float m_speed, m_timeAlive, m_timeToLive, m_damage, m_rotation;
	//sf::Vector2f m_pos, m_dir;
	m_target = target;
	m_pos = pos;
	m_speed = speed;
	m_timeToLive = timeToLive;
	m_timeAlive = 0;
	m_sprite.setTexture(*texture);
	m_friction = -10;
	
	m_dir = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(m_rotation)), sin(VectorMath::GetInstance()->ToRadian(m_rotation))));
	sf::Vector2u size = texture->getSize();
	intercept();//set the initial path
	m_rotation = angleBetween;
	rotationSpeed = 100;
	m_radius = size.x / 2;
	m_sprite.setOrigin(size.x / 2, size.y / 2);
	m_sprite.setRotation(m_rotation);
	m_sprite.setPosition(m_pos);
}
bool BasicBullet::Update(float time)
{
	//s=ut+(1/2)a(t(t))
	m_pos += m_dir * m_speed * time + m_dir * 0.5f* m_friction * time *time;
	m_speed += m_friction* time;
	m_sprite.setPosition(m_pos);
	m_timeAlive += time;
	
	if (m_timeToLive <= m_timeAlive|| FactoryManager::GetInstance()->IsColiding(this))
	{
		return false;
	}

	return true;
}
bool BasicBullet::UpdatePredator(float time)
{
	
	intercept();//set course
	//move
	Rotate(time);
	m_pos += m_dir * m_speed * time;
	m_sprite.setPosition(m_pos);
	m_timeAlive += time;

	if (m_timeToLive <= m_timeAlive || m_target->isColliding(m_pos,m_radius))
	{
		return false;
	}

	return true;
}
void BasicBullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
sf::Vector2f BasicBullet::GetPosition(){ return m_pos; }
float BasicBullet::GetRadius(){ return m_radius; }

void BasicBullet::seek(sf::Vector2f target)
{
	//Velocity = target.position - my.position
	sf::Vector2f vel = target - m_pos;
	//Velocity = normalize(velocity)
	vel = VectorMath::GetInstance()->Normalise(vel);
	//Orientation = getNewOrientation(orientation, velocity)
	angleBetween = VectorMath::GetInstance()->GetAngleBetween(m_dir, vel);

}
void BasicBullet::intercept()
{
	//direction = target.position - my.position
	sf::Vector2f direction = m_target->getPosition() - m_pos;
	//distance = direction.length
	float distance = VectorMath::GetInstance()->GetLength(direction);
	//speed = my.velocity.length
	//if speed <= distance / maxTimePrediction:
	float maxTimePrediction = m_timeToLive - m_timeAlive;
	float timePrediction = 0;
	if (m_speed <= distance / maxTimePrediction)
	{
		//timePrediction = maxTimeprediction
		timePrediction = maxTimePrediction;
	}
	//else
	else
	{
		//timePrediction = distance / speed
		timePrediction = distance / m_speed;

	}
	//newtarget.position = target.position + target.velocity * timePrediction
	sf::Vector2f newTarget = m_target->getPosition() + m_target->getDirection() * m_target->getSpeed() * timePrediction;
	//seek(newTarget)
	seek(newTarget);
}
void BasicBullet::Rotate(float time)
{
	//cout << angleBetween << endl;
	if (angleBetween > 0)
	{
		m_rotation += rotationSpeed * time;
	}
	else if (angleBetween < 0)
	{
		m_rotation -= rotationSpeed * time;
	}
	m_dir = VectorMath::GetInstance()->Normalise(sf::Vector2f(cos(VectorMath::GetInstance()->ToRadian(m_rotation)), sin(VectorMath::GetInstance()->ToRadian(m_rotation))));
}