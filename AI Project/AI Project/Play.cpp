#include "Play.h"


PlayGame::PlayGame(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	player = new Player(SCREEN_WIDTH,SCREEN_HEIGHT);
	player->SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	EnemyManager::GetInstance()->Init(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void PlayGame::Init()
{
	
}

void PlayGame::Update(float time){
	EnemyManager::GetInstance()->Update(time, player);
	player->Update(time);
}

void PlayGame::Draw(sf::RenderWindow& window){
	player->Draw(window);
	EnemyManager::GetInstance()->Draw(window);
}

void PlayGame::ResetAll(){

}

