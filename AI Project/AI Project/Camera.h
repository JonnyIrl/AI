#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Common.h"

using namespace std;



class Camera
{
private:
	static bool instanceFlag;
	static Camera* instance;
	sf::View camView;
	Camera()
	{
	}
public:
	static Camera* GetInstance();
	~Camera()
	{
		instanceFlag = false;
		
	}
	void Init(int w, int h);
	void setCentre(sf::Vector2f pos);
	sf::View getView();
	void setView(sf::View v);
	void setViewPosition(sf::Vector2f pos);
	sf::Vector2f getViewPosition();
};
#endif