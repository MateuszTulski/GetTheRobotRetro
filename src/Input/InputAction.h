#ifndef INPUT_INPUTACTION_H_
#define INPUT_INPUTACTION_H_

#include <stdint.h>
#include <functional>

// Typedef
using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

using InputAction = std::function<void(uint32_t deltaTime, InputState)>;

struct ButtonAction{
	InputKey key;
	InputAction action;
};

struct MousePosition{
	int32_t xPos, yPos;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& mousePosition)>;

struct MouseButtonAction{
	MouseButton mouseButton;
	MouseInputAction mouseInputAction;
};

#endif /* INPUT_INPUTACTION_H_ */
