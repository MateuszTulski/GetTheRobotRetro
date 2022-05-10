#ifndef SRC_GAMEOBJECTS_PLAYERANIMATIONS_H_
#define SRC_GAMEOBJECTS_PLAYERANIMATIONS_H_

#include "Enums.h"
#include "Animator.h"
#include "Animation.h"

class Screen;

class PlayerAnimations{

public:
	PlayerAnimations();
	bool InitAnimations();

	void Update(const PlayerState& state);
	void Draw(Screen& screen, Vec2D pivotPoint, int direction);

private:
	PlayerState lastState;
	Animator mAnimator;

	bool NewAnimationState(const PlayerState& state);
	void SetNewAnimation();
};



#endif /* SRC_GAMEOBJECTS_PLAYERANIMATIONS_H_ */
