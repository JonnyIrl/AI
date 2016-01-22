#include "Controls.h"

Controls::Controls(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (LoadTextures())
	{
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(0, 0));
		sprite.setScale(sf::Vector2f(1, 1));

		playRectangle.setSize(sf::Vector2f(250, 100));
		playRectangle.setTexture(&playTexture);
		playRectangle.setPosition(sf::Vector2f(900, 700));

	}

}

bool Controls::LoadTextures()
{
	if (!texture.loadFromFile("Assets/Controls/controlsMenu.png"))
	{
		return false;
	}

	if (!playTexture.loadFromFile("Assets/Controls/play.png"))
	{
		return false;
	}

	return true;
}

void Controls::Init()
{

}
void Controls::Update(float time, sf::RenderWindow& window, sf::Event Event)
{

	if (Event.type == Event.MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
	{
		// left click...

		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		sf::Vector2f converted = window.mapPixelToCoords(mousepos);
		sf::RectangleShape mouseRect;
		mouseRect.setSize(sf::Vector2f(1, 1));
		mouseRect.setPosition(converted);

		if (mouseRect.getGlobalBounds().intersects(playRectangle.getGlobalBounds()))
		{
			GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->PLAY);
		}
	}

}
void Controls::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(playRectangle);
}