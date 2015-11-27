#ifndef _PLAY_H_
#define _PLAY_H_

#include <iostream>

#include "GameStateController.h"
#include "Player.h"
#include "Enemy.h"


class Play{
private:
	Player* player;
public:
	Play(int w, int h);
	~Play(){
		delete player;
	}
	void Init();
	void Update(float time);
	void Draw(sf::RenderWindow& window);
	void ResetAll();

};
#endif
