#include "Common.h"
#include "GameStateController.h"
#include "Menu.h"
#include "Play.h"
#include "Pause.h"
#include "Splash.h"
#include "ScoreScreen.h"



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

 int SCREEN_WIDTH = 1280;
 int SCREEN_HEIGHT = 800;

int main()
{
	//gamestates
	Menu* menu;
	PlayGame* play;
	Pause* pause;
	Splash* splash;
	ScoreScreen* scoreScreen;

	// Create the main window 
	//Screen dimension constants

	
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFML First Program");
	
	/*Initialsie the game modes*/
	menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT);
	play = new PlayGame(SCREEN_WIDTH, SCREEN_HEIGHT);
	pause = new Pause(SCREEN_WIDTH, SCREEN_HEIGHT);
	splash = new Splash(SCREEN_WIDTH, SCREEN_HEIGHT);
	scoreScreen = new ScoreScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	//clock & frame rate
	sf::Clock mclock;
	sf::Time timeSinceLastUpdate;
	window.setFramerateLimit(60);
	// Start game loop 
	while (window.isOpen())
	{
		//get time between frames
		timeSinceLastUpdate = mclock.getElapsedTime();
		float time = timeSinceLastUpdate.asSeconds();//get update time
		mclock.restart();


		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}
		//updates
		switch (GameStateController::GetInstance()->getGameState())
		{
		case GameStateController::MENU:
			menu->Update(time);
			break;
		case GameStateController::PLAY:
			play->Update(time, timeSinceLastUpdate);
			break;
		case GameStateController::CREDITS:
			break;
		case GameStateController::PAUSE:
			break;
		case GameStateController::SPLASH:
			break;
		case GameStateController::SCORESCREEN:
			break;
		}//end switch



		//prepare frame
		window.clear(sf::Color::White);

		//draw
		switch (GameStateController::GetInstance()->getGameState())
		{
		case GameStateController::MENU:
			menu->Draw(window);
			break;
		case GameStateController::PLAY:
			play->Draw(window);
			break;
		case GameStateController::CREDITS:
			break;
		case GameStateController::PAUSE:
			break;
		case GameStateController::SPLASH:
			break;
		case GameStateController::SCORESCREEN:
			break;
		}//end switch


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame
	
	//delete pointers
	delete menu;
	delete play;
	delete pause;
	delete splash;
	delete scoreScreen;

	return EXIT_SUCCESS;
}