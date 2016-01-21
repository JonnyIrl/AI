#ifndef _PLAY_H_
#define _PLAY_H_

#include <iostream>

#include "Common.h"
#include "GameStateController.h"
#include "Player.h"
#include "EnemyManager.h"
#include "FactoryManager.h"
#include "BulletManager.h"
#include "SwarmManager.h"
#include "Camera.h"
#include "HUD.h"
#include "MiniMap.h"
#include "ObstacleManager.h"
#include "PowerupManager.h"

class PlayGame{
private:
	Player* player;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Texture miniMapTexture;
	sf::Sprite miniMapSprite;

public:
	PlayGame( int w, int h);
	~PlayGame(){
		delete player;
	}
	void Init();
	void Update(float time, sf::Time animationTime);
	void Draw(sf::RenderWindow& window);
	void ResetAll();

};
#endif
