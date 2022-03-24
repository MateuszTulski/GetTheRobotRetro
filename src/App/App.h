#ifndef APP_APP_H_
#define APP_APP_H_

#include "Screen.h"
#include "Scene.h"
#include "InputController.h"
#include "BitmapFont.h"
#include <stdint.h>
#include <memory>
#include <vector>

struct SDL_Window;

class App{
public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t GetWidht(){return mScreen.GetWidth();}
	inline uint32_t GetHeight(){return mScreen.GetHeight();}

	inline BitmapFont GetAppFont() const {return mFont;}

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene();	// Current

	static const std::string& GetBasePath();

private:
	BitmapFont mFont;
	Screen mScreen;
	SDL_Window * mnoptrWindow;
	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
};

#endif /* APP_APP_H_ */
