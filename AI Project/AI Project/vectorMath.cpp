#include "vectorMath.h"


bool VectorMath::instanceFlag = false;
VectorMath* VectorMath::instance = NULL;


VectorMath* VectorMath::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new VectorMath;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
sf::Vector2f VectorMath::Normalise(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return sf::Vector2f(vec.x / length, vec.y / length);
}
float VectorMath::ToRadian(float deg)
{
	return (deg* M_PI) / 180;
}
float VectorMath::GetLength(sf::Vector2f vec)
{
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}
float VectorMath::GetAngleBetween(sf::Vector2f vec1, sf::Vector2f vec2)
{
	float dot = GetDotProduct(vec1, vec2);
	float det = vec1.x * vec2.y - vec1.y*vec2.x;
	return ToRadian(atan2(det, dot));	
}
float VectorMath::GetDotProduct(sf::Vector2f vec1, sf::Vector2f vec2)
{

	return (vec1.x * vec2.x) + (vec1.y * vec2.y);

}
float VectorMath::getDistanceBetween(sf::Vector2f vec1, sf::Vector2f vec2)
{
	sf::Vector2f temp = vec2 - vec1;
	return GetLength(temp);
}