#include <GameControlsActions.h>
#include <SDL2/SDL.h>
#include <iostream>

GameControlsActions::GameControlsActions(): mMouseMovedAction(nullptr){

}

InputAction GameControlsActions::GetActionForKey(InputKey key){
	for(const auto& buttonAction : mButtonActions){
		if(key == buttonAction.key)
		{
			return buttonAction.action;
		}
	}
	return [](uint32_t, InputState){};
}

void GameControlsActions::AddInputActionForKey(const ButtonAction& buttonAction){
	mButtonActions.push_back(buttonAction);
}

void GameControlsActions::ClearAll(){
	mButtonActions.clear();
}

bool GameControlsActions::IsPressed(InputState state){
	return state == SDL_PRESSED;
}

bool GameControlsActions::IsReleased(InputState state){
	return state == SDL_RELEASED;
}

InputKey GameControlsActions::ActionKey(){
	return static_cast<InputKey>(SDLK_a);
}
InputKey GameControlsActions::CancelKey(){
	return static_cast<InputKey>(SDLK_s);
}

InputKey GameControlsActions::RightKey(){
	return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameControlsActions::LeftKey(){
	return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameControlsActions::UpKey(){
	return static_cast<InputKey>(SDLK_UP);
}

InputKey GameControlsActions::DownKey(){
	return static_cast<InputKey>(SDLK_DOWN);
}

InputKey GameControlsActions::JumpKey(){
	return static_cast<InputKey>(SDLK_SPACE);
}

MouseButton GameControlsActions::LeftMouseButton(){
	return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameControlsActions::RigthMouseButton(){
	return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}

MouseInputAction GameControlsActions::GetMouseInputAction(MouseButton mouseButton){
	for(const auto& buttonAction : mMouseButtonActions){
		if(buttonAction.mouseButton == mouseButton){

			return buttonAction.mouseInputAction;
		}
	}

	return [](InputState state, const MousePosition& mousePosition){};
}
void GameControlsActions::AddMouseInputActionForKey(const MouseButtonAction& mouseButtonAction){
	mMouseButtonActions.push_back(mouseButtonAction);
}

