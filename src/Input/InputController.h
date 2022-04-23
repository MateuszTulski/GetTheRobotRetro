#ifndef INPUT_INPUTCONTROLLER_H_
#define INPUT_INPUTCONTROLLER_H_

#include <SDL2/SDL.h>
#include "InputAction.h"
#include "GameController.h"

class InputController{

public:
	InputController();
	void InitInputController(InputAction quitAction);
	void Update(uint32_t deltaTime);
	void SetGameController(GameController* controller);

private:
	InputAction mQuit;
	GameController* mnoptrGameController;
};


#endif /* INPUT_INPUTCONTROLLER_H_ */
