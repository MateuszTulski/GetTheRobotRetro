#ifndef APP_APP_H_
#define APP_APP_H_

#include "Screen.h"
#include "Scene.h"
#include "InputController.h"
#include "BitmapFont.h"
#include "Vec2D.h"
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

	inline Vec2D GetScreenCenter() const {return Vec2D(mScreen.GetWidth()/2, mScreen.GetHeight()/2);}

	inline BitmapFont GetAppFont() const {return mFont;}

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene();	// Current

	static const std::string& GetBasePath();

	void SetSceneCamera(const Vec2D& position, std::shared_ptr<Camera>& cameraPtr);

private:
	BitmapFont mFont;
	Screen mScreen;
	SDL_Window * mnoptrWindow;
	std::vector<std::unique_ptr<Scene>> mSceneStack;
	std::shared_ptr<Camera> mActiveCameraPtr;
	InputController mInputController;
};

#endif /* APP_APP_H_ */
