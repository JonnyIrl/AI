#include "Play.h"


PlayGame::PlayGame(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	player = new Player(SCREEN_WIDTH,SCREEN_HEIGHT);
	player->SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	EnemyManager::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	BulletManager::GetInstance()->Init();
	if (!backgroundTexture.loadFromFile("Assets/background.png"))
	{
		cout << "background image did not load " << endl;
	}
	sf::Vector2u size = backgroundTexture.getSize();
	background.setTexture(backgroundTexture);
	background.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	background.setScale(sf::Vector2f((SCREEN_WIDTH * 3) / size.x, (SCREEN_HEIGHT * 3) / size.y));
	background.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	if (!miniMapTexture.loadFromFile("Assets/Minimap.png"))
	{
		cout << "minimap image did not load " << endl;
	}
	size = miniMapTexture.getSize();
	miniMapSprite.setTexture(miniMapTexture);
	//miniMapSprite.setScale(sf::Vector2f(SCREEN_WIDTH / size.x, SCREEN_HEIGHT / size.y));


	Camera::GetInstance()->Init(SCREEN_WIDTH,SCREEN_HEIGHT);
	MiniMap::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void PlayGame::Init()
{
	
}

void PlayGame::Update(float time){
	EnemyManager::GetInstance()->Update(time, player);
	BulletManager::GetInstance()->Update(time);
	player->Update(time);
}

void PlayGame::Draw(sf::RenderWindow& window){

	//game Window
	window.draw(background);
	
	EnemyManager::GetInstance()->Draw(window);
	BulletManager::GetInstance()->Draw(window);
	player->Draw(window);
	//MiniMap
	window.setView(MiniMap::GetInstance()->getView());
	window.draw(background);
	EnemyManager::GetInstance()->Draw(window);
	BulletManager::GetInstance()->Draw(window);
	player->Draw(window);
	window.setView(MiniMap::GetInstance()->getStaticView());
	window.draw(miniMapSprite);
	//reset view
	window.setView(Camera::GetInstance()->getView());
}

void PlayGame::ResetAll(){

}

