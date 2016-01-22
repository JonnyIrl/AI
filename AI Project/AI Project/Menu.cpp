#include "Menu.h"

Menu::Menu(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (LoadTextures())
	{
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(0, 0));
		sprite.setScale(sf::Vector2f(1, 1));

		playRectangle.setSize(sf::Vector2f(250, 100));
		playRectangle.setTexture(&playTexture);
		playRectangle.setPosition(sf::Vector2f(500, 200));

		quitRectangle.setSize(sf::Vector2f(250, 100));
		quitRectangle.setTexture(&quitTexture);
		quitRectangle.setPosition(sf::Vector2f(500, 600));

		controlsRectangle.setSize(sf::Vector2f(500, 100));
		controlsRectangle.setTexture(&controlsTexture);
		controlsRectangle.setPosition(sf::Vector2f(500, 400));
	}

}

bool Menu::LoadTextures()
{
	if (!texture.loadFromFile("Assets/Menu/menu.png"))
	{
		return false;
	}

	if (!playTexture.loadFromFile("Assets/Menu/play.png"))
	{
		return false;
	}

	if (!quitTexture.loadFromFile("Assets/Menu/quit.png"))
	{
		return false;
	}

	if (!controlsTexture.loadFromFile("Assets/Menu/controls.png"))
	{
		return false;
	}

	return true;
}

void Menu::Init()
{

}
void Menu::Update(float time, sf::RenderWindow& window, sf::Event Event)
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

		if (mouseRect.getGlobalBounds().intersects(controlsRectangle.getGlobalBounds()))
		{
			GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->CONTROLS);
		}

		if (mouseRect.getGlobalBounds().intersects(quitRectangle.getGlobalBounds()))
		{
			window.close();
		}


	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		//GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->PLAY);
	}
}
void Menu::Draw(sf::RenderWindow& window)
{

	window.draw(sprite);
	window.draw(playRectangle);
	window.draw(quitRectangle);
	window.draw(controlsRectangle);
}