#ifndef _HUD_H_
#define _HUD_H_

#include "Common.h"

using namespace std;



class HUD
{
private:
	static bool instanceFlag;
	static HUD* instance;
	sf::View view;
	sf::View staticView;

	HUD()
	{
	}
public:
	static HUD* GetInstance();
	~HUD()
	{
		instanceFlag = false;

	}
	void Init(int w, int h);
	sf::View getView();
	sf::View getStaticView();
	void setView(sf::View v);
	void setViewPosition(sf::Vector2f pos);

};
#endif