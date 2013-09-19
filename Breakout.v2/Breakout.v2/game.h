#include "stdafx.h"

class game
{
private:
	const static int WIDTH;
	const static int HEIGHT;

	const static int MAX_FRAMERATE;
	const static int MAX_FRAMESKIP;

	enum gameState { Initializing, Paused, Playing, Exiting};
	
	static gameState _gameState;

	void gameLoop();
public:
	static void start();
};