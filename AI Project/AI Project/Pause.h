#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "Common.h"
#include "GameStateController.h"
#include "Play.h"


class Pause
{
private:
public:

	Pause(int w, int h);
	~Pause()
	{
		
	}
	void Init();
	void Update(float time);
	void Draw(PlayGame *, sf::RenderWindow&);


};
#endif
