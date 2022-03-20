#ifndef INPUT_GAMECONTROLLER_H_
#define INPUT_GAMECONTROLLER_H_

#include <SDL2/SDL.h>
#include "InputAction.h"
#include <vector>

class GameController{
public:
	GameController();
	InputAction GetActionForKey(InputKey key);
	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();

	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);

	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();

	static MouseButton LeftMouseButton();
	static MouseButton RigthMouseButton();

	// Mouse inputs
	inline const MouseMovedAction& GetMouseMovedAction(){ return mMouseMovedAction; }
	inline void SetMouseMovedAction(const MouseMovedAction& action){mMouseMovedAction = action;}

	MouseInputAction GetMouseInputAction(MouseButton mouseButton);
	void AddMouseInputActionForKey(const MouseButtonAction& mouseButtonAction);

private:
	std::vector<ButtonAction> mButtonActions;
	std::vector<MouseButtonAction> mMouseButtonActions;
	MouseMovedAction mMouseMovedAction;
};



#endif /* INPUT_GAMECONTROLLER_H_ */
