#ifndef _SCORESCREEN_H_
#define _SCORESCREEN_H_

#include "Common.h"

#include "GameStateController.h"



class ScoreScreen
{
private:
	
public:

	ScoreScreen(int w, int h);
	~ScoreScreen()
	{
		
	}
	void Init();
	void Update();
	void Draw();


};
#endif
