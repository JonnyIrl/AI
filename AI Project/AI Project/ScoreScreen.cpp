#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (!texture.loadFromFile("Assets/scoreScreen.png"))
	{

	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(1, 1));
	view1.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	
}

void ScoreScreen::Init()
{
}
void ScoreScreen::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->MENU);
	}
}
void ScoreScreen::Draw(sf::RenderWindow& window)
{
	window.setView(view1);
	window.draw(sprite);
}



