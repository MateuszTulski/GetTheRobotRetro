#include "App.h"
#include "PursuitScene.h"
#include "MenuScene.h"
#include "InputController.h"
#include "Camera.h"
#include <cassert>
#include <iostream>
#include <memory>

App& App::Singleton(){
	static App theApp;
	return theApp;
}
bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	if(!mFont.LoadFont("HemiFont")){
		return false;
	}
	mFont.SetFontHeight(18);

	mnoptrWindow = mScreen.Init(width, height, mag);

	std::unique_ptr<MenuScene> menuScene = std::make_unique<MenuScene>();
	PushScene(std::move(menuScene));

	return mnoptrWindow != nullptr;
}

void App::Run(){
	bool running = true;

	uint32_t lastTick = SDL_GetTicks();
	uint32_t currentTick = lastTick;

	uint32_t deltaTime = 10;
	uint32_t accumulator = 0;

	mInputController.InitInputController([&running](uint32_t deltaTime, InputState state){
		running = false;
	});

	while(running){

		currentTick = SDL_GetTicks();
		uint32_t frameTime = currentTick - lastTick;

		if(frameTime > 300){
			frameTime = 300;
		}

		lastTick = currentTick;;
		accumulator += frameTime;

		// INPUT
		mInputController.Update(deltaTime);

		Scene* topScene = TopScene();
		assert(topScene && "Scene Missing!");

		if(topScene){
			// UPDATE
			while(accumulator >= deltaTime)
			{
				topScene->Update(deltaTime);
				accumulator -= deltaTime;
			}

			// RENDER
			topScene->Draw(mScreen);
		}

		mScreen.SwapScreens();
	}
}

void App::PushScene(std::unique_ptr<Scene> scene){
	if(scene){
		scene->Init();
		// Set GameController
		mInputController.SetGameController(scene->GetGameController());
		// Set title
		SDL_SetWindowTitle(mnoptrWindow, scene->GetSceneName().c_str());
		// Push scene to the stack
		mSceneStack.emplace_back(std::move(scene));
	}
}

void App::PopScene(){
	if(mSceneStack.size()>1){
		mScreen.RemoveSceneCamera();
		mActiveCameraPtr.reset();
		// Remove scene from stack
		mSceneStack.pop_back();
	}
	if(TopScene()){
		mInputController.SetGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}

Scene* App::TopScene(){	// Current
	if(mSceneStack.empty()){
		return nullptr;
	}
	return mSceneStack.back().get();
}

const std::string& App::GetBasePath()
{
	static std::string path = "src/";
	return path;
}

void App::SetSceneCamera(const Vec2D& position, std::shared_ptr<Camera>& cameraPtr)
{
	Camera camera;
	camera.Init(position);

	mActiveCameraPtr = std::make_shared<Camera>(std::move(camera));
	mScreen.SetSceneCamera(mActiveCameraPtr);

	cameraPtr = mActiveCameraPtr;
}
