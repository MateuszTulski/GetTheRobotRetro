#include <SDL2/SDL.h>
#include "Utils.h"
#include "App.h"

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 224;
const int MAGNIFICATION = 4;

int main() {

	if(App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
	{
		App::Singleton().Run();
	}
	return 0;
}


