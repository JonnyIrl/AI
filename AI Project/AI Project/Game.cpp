#include "Common.h"
#include "Player.h"



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	Player player;
	player.SetPosition(sf::Vector2f(400, 300));



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

		//update here

		player.Update(time);
		
		//prepare frame
		window.clear();

		//draw here

		player.Draw(window);


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}