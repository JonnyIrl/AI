#include "Play.h"


PlayGame::PlayGame( int w,  int h)
{

	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	player = new Player(SCREEN_WIDTH,SCREEN_HEIGHT);
	player->SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	//EnemyManager::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	FactoryManager::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	SwarmManager::GetInstance()->Init(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	ObstacleManager::GetInstance()->Init(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	PowerupManager::GetInstance()->Init(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	BulletManager::GetInstance()->Init();
	if (!backgroundTexture.loadFromFile("Assets/newBackground.png"))
	{
		cout << "background image did not load " << endl;
	}
	sf::Vector2u size = backgroundTexture.getSize();
	background.setTexture(backgroundTexture);
	//background.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	//background.setScale(sf::Vector2f(1.5f, 1.2f));

	//background.setScale(sf::Vector2f((SCREEN_WIDTH * 3.15f) / size.x, (SCREEN_HEIGHT * 3.15f) / size.y));
	cout << "Width = " << background.getGlobalBounds().width << "Height = " << background.getGlobalBounds().height << endl;
	background.setPosition(-2000, -1200);

	//background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	if (!miniMapTexture.loadFromFile("Assets/Minimap.png"))
	{
		cout << "minimap image did not load " << endl;
	}
	size = miniMapTexture.getSize();
	miniMapSprite.setTexture(miniMapTexture);
	miniMapSprite.setScale(sf::Vector2f(SCREEN_WIDTH / size.x, SCREEN_HEIGHT / size.y));
	miniMapSprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	Camera::GetInstance()->Init(SCREEN_WIDTH,SCREEN_HEIGHT);
	MiniMap::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	HUD::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);

}

void PlayGame::Init()
{
	
}

void PlayGame::Update(float time, sf::Time animationTime){
	EnemyManager::GetInstance()->Update(time, player);
	FactoryManager::GetInstance()->Update(time, player);
	PowerupManager::GetInstance()->Update(time, player);
	SwarmManager::GetInstance()->Update(time, player);
	BulletManager::GetInstance()->Update(time);
	ObstacleManager::GetInstance()->Update(animationTime, player);
	if (player->Alive())
	{
		player->Update(time, animationTime);
	
	}
	else
	{
		ResetAll();
		GameStateController::GetInstance()->SetGameState(GameStateController::GetInstance()->SCORESCREEN);
	}

	
}

void PlayGame::Draw(sf::RenderWindow& window){

	//game Window
	window.draw(background);

	EnemyManager::GetInstance()->Draw(window);
	FactoryManager::GetInstance()->Draw(window);
	SwarmManager::GetInstance()->Draw(window);
	BulletManager::GetInstance()->Draw(window);
	ObstacleManager::GetInstance()->Draw(window);
	PowerupManager::GetInstance()->Draw(window);
	if (player->Alive())
	{
		player->Draw(window);
	}
	//MiniMap
	window.setView(MiniMap::GetInstance()->getView());
	window.draw(background);
	EnemyManager::GetInstance()->Draw(window);
	FactoryManager::GetInstance()->Draw(window);
	SwarmManager::GetInstance()->Draw(window);
	BulletManager::GetInstance()->Draw(window);
	ObstacleManager::GetInstance()->Draw(window);
	PowerupManager::GetInstance()->Draw(window);
	player->Draw(window);
	window.setView(MiniMap::GetInstance()->getStaticView());
	window.draw(miniMapSprite);

	//HUD VIEW
	window.setView(HUD::GetInstance()->getView());
	window.draw(player->PlayerHealthHUD());
	window.draw(player->PlayerShieldHUD());
	//reset view
	window.setView(Camera::GetInstance()->getView());
}

void PlayGame::ResetAll(){

	delete player;
	player = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
	player->SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	//enemymanger reset all 
	EnemyManager::GetInstance()->reset();
	//swarm manager reset all
	SwarmManager::GetInstance()->Reset();
	//obstacle manager reset all
	ObstacleManager::GetInstance()->Reset();
	//factory manager rest all
	FactoryManager::GetInstance()->Reset();
	//bullet managher reset all 
	BulletManager::GetInstance()->reset();
	//powerup manager reset all
	PowerupManager::GetInstance()->Reset();


}

