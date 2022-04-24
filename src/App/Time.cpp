#include "Time.h"
#include "GlobalSettings.h"

#include <iostream>

Time::Time() : frameRate(DEFAULT_APP_FPS), frame(0), lastTickTime(0), currentFrameDuration(0), prevFrameDuration(0), timeScale(1){

}

void Time::UpdateTime(UpdateAction executeFrame){

	uint32_t currentTickTime = SDL_GetTicks();

	currentFrameDuration = currentTickTime - lastTickTime;

	if(currentFrameDuration >= (1000.0f / frameRate))
	{
		executeFrame();
		prevFrameDuration = currentFrameDuration;
		lastTickTime = currentTickTime;
		frame ++;
	}

}


float Time::DeltaTime(){

	return  static_cast<float>(prevFrameDuration) / 1000.0f;
}

float Time::AppTime(){

	return  static_cast<float>(SDL_GetTicks()) / 1000.0f;
}










//currentTickTime = SDL_GetTicks();
//uint32_t lastTickDurationTime = currentTickTime - lastTickTime;
//
//
//lastTickTime = currentTickTime;;
//accumulator += lastTickDurationTime;
//
//// INPUT
//mInputController.Update(deltaTime);
//
//Scene* topScene = TopScene();
//assert(topScene && "Scene Missing!");
