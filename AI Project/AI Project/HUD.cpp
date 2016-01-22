#include "HUD.h"


bool HUD::instanceFlag = false;
HUD* HUD::instance = NULL;

HUD* HUD::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new HUD();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void HUD::Init(int w, int h)
{

	view = sf::View(sf::FloatRect(0, 0, w, h));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));

}
sf::View HUD::getView()
{
	return view;
}
void HUD::setView(sf::View v)
{
	view = v;
}
void HUD::setViewPosition(sf::Vector2f pos)
{
	view.setCenter(pos);
}
sf::View HUD::getStaticView()
{
	return staticView;
}