#ifndef _GAMESTATECONTROLLER_H_
#define _GAMESTATECONTROLLER_H_

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>


class GameStateController
{
private:
	static bool instanceFlag;
	static GameStateController* instance;
	GameStateController()
	{
		GameState = MENU;
	}
	int GameState;
	
	
public:
	static const int MENU = 0, PLAY = 1, PAUSE = 2, GAMEOVER = 3, CREDITS = 4, SPLASH = 5, CONTROLS = 6, SCORESCREEN = 7;
	static GameStateController* GetInstance();
	~GameStateController()
	{
		instanceFlag = false;
	}
	void SetGameState(int);
	int getGameState() const;

};
#endif