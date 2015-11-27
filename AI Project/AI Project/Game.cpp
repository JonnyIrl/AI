#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateController.h"
#include "Menu.h"
#include "Play.h"
#include "Pause.h"
#include "Splash.h"
#include "ScoreScreen.h"


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{

	//gamestates
	Menu* menu;
	Play* play;
	Pause* pause;
	Splash* splash;
	ScoreScreen* scoreScreen;


	// Create the main window 
	//Screen dimension constants

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 800;
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFML First Program");

	//Player player;
	//player.SetPosition(sf::Vector2f(400, 300));
	//float speed;
	//float angle;
	//const int maxEnemy = 100;
	//Enemy enemy_Array[maxEnemy];


	//for (int i = 0; i < maxEnemy; i++)//assign random speed and position to each triangle
	//{
	//	angle = (rand() % 360 + 1);
	//	sf::Vector2f pos((rand() % 720 + 21), (rand() % 520 + 21));
	//	enemy_Array[i].SetPosition(pos);
	//}// end for (int i = 0 ; i < maxTriangles;i++)
	
	/*Initialsie the game modes*/
	menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT);
	play = new Play(SCREEN_WIDTH, SCREEN_HEIGHT);
	pause = new Pause(SCREEN_WIDTH, SCREEN_HEIGHT);
	splash = new Splash(SCREEN_WIDTH, SCREEN_HEIGHT);
	scoreScreen = new ScoreScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->MENU);


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
			play->Update(time);
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


	/*	player.Update(time);
		
		for (int i = 0; i < maxEnemy; i++)
		{
			enemy_Array[i].Update(time, player.GetPosition());
		}
*/
		//prepare frame
		window.clear();

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
		//player.Draw(window);
		//for (int i = 0; i < maxEnemy; i++)
		//{
		//	enemy_Array[i].Draw(window);
		//}// end for (int i = 0; i < maxEnemy ;i++)

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