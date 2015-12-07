#include "MiniMap.h"


bool MiniMap::instanceFlag = false;
MiniMap* MiniMap::instance = NULL;

MiniMap* MiniMap::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new MiniMap();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void MiniMap::Init(int w, int h)
{
	view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	//view.setSize(w*3, h*3);
	staticView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));



}
sf::View MiniMap::getView()
{
	return view;
}
void MiniMap::setView(sf::View v)
{
	view = v;
}
void MiniMap::setViewPosition(sf::Vector2f pos)
{
	view.setCenter(pos);
}
sf::View MiniMap::getStaticView()
{
	return staticView;
}