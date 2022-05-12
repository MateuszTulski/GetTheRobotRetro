#include "InputController.h"
#include <SDL2/SDL.h>
#include <iostream>

InputController::InputController():mQuit(nullptr), mnoptrGameController(nullptr){
}

void InputController::InitInputController(InputAction quitAction){
	mQuit = quitAction;
}

void InputController::Update(uint32_t deltaTime){

	SDL_Event sdlEvent;

	while(SDL_PollEvent(&sdlEvent)){
		switch(sdlEvent.type){
		case SDL_QUIT:
		{
			mQuit(deltaTime, SDL_PRESSED);
		}
			break;
		case SDL_MOUSEMOTION:
			if(mnoptrGameController){
				if(MouseMovedAction mouseMoveAction = mnoptrGameController->GetMouseMovedAction()){
					MousePosition position;
					position.xPos = sdlEvent.motion.x;
					position.yPos = sdlEvent.motion.y;
					mouseMoveAction(position);
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			if(mnoptrGameController){
				MouseInputAction mouseAction = mnoptrGameController->GetMouseInputAction(static_cast<MouseButton>(sdlEvent.button.button));
					MousePosition position;
					position.xPos = sdlEvent.motion.x;
					position.yPos = sdlEvent.motion.y;
					mouseAction(static_cast<InputState>(sdlEvent.button.state), position);

			}
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if(mnoptrGameController){
				InputAction action = mnoptrGameController->GetActionForKey(sdlEvent.key.keysym.sym);
				action(deltaTime, static_cast<InputState>(sdlEvent.key.state));
			}
			break;
		}
	}
}

void InputController::SetGameController(GameControlsActions* controller){
	mnoptrGameController = controller;
}

