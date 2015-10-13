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
private:
	//variables
	static bool instanceFlag;
	static VectorMath* instance;
	
	
};




#endif 

