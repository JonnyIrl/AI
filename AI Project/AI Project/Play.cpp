#include "Play.h"


Play::Play( int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	player = new Player(SCREEN_WIDTH,SCREEN_HEIGHT);
	player->SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

}

void Play::Init()
{

}

void Play::Update(float time){
	player->Update(time);
}

void Play::Draw(sf::RenderWindow& window){
	player->Draw(window);
}





void Play::ResetAll(){

}

