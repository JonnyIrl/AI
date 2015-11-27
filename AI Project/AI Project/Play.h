#ifndef _PLAY_H_
#define _PLAY_H_

#include <iostream>

#include "GameStateController.h"
#include "Player.h"
#include "EnemyManager.h"

class PlayGame{
private:
	Player* player;
public:
	PlayGame(int w, int h);
	~PlayGame(){
		delete player;
	}
	void Init();
	void Update(float time);
	void Draw(sf::RenderWindow& window);
	void ResetAll();

};
#endif
