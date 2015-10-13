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
float VectorMath::GetAngleBetween(sf::Vector2f vec1, sf::Vector2f vec2)
{

	//to be completed

	return 1;
}