#ifndef INPUT_INPUTCONTROLLER_H_
#define INPUT_INPUTCONTROLLER_H_

#include <GameControlsActions.h>
#include <SDL2/SDL.h>
#include "InputAction.h"

class InputController{

public:
	InputController();
	void InitInputController(InputAction quitAction);
	void Update(uint32_t deltaTime);
	void SetGameController(GameControlsActions* controller);

private:
	InputAction mQuit;
	GameControlsActions* mnoptrGameController;
};


#endif /* INPUT_INPUTCONTROLLER_H_ */
