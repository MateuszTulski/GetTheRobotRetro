#include <SDL2/SDL.h>
#include "Utils.h"
#include "App.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAGNIFICATION = 2;

int main() {

	if(App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
	{
		App::Singleton().Run();
	}
	return 0;
}


