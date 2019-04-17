#include "Engine.h"



int main( void )
{

	Engine *engine = new Engine();
	engine->init();
	engine->loop();

	delete engine;

	return 0;
}

