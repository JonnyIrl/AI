#ifndef VECTORMATH
#define VECTORMATH
#include "Common.h"


using namespace std;


class VectorMath
{

public:
	VectorMath(){}
	static VectorMath* GetInstance();
	~VectorMath()
	{
		instanceFlag = false;
	}
	//methoda
	sf::Vector2f Normalise(sf::Vector2f vec);
	float ToRadian(float deg);
	float GetLength(sf::Vector2f vec);
	float GetAngleBetween(sf::Vector2f vec1, sf::Vector2f vec2);
	float GetDotProduct(sf::Vector2f vec1, sf::Vector2f vec2);
private:
	//variables
	static bool instanceFlag;
	static VectorMath* instance;
	
	
};




#endif 

