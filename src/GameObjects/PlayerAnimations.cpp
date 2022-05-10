#include "PlayerAnimations.h"

PlayerAnimations::PlayerAnimations() : lastState(PlayerState::idle){

}

void PlayerAnimations::Update(const PlayerState& state){
	mAnimator.Update();

	if(NewAnimationState(state)){
		SetNewAnimation();
	}
}

void PlayerAnimations::Draw(Screen& screen, Vec2D pivotPoint, int direction){

	if(direction > 0){
		mAnimator.DrawActiveAnimation(screen, pivotPoint);
	}else{
		mAnimator.DrawFlippedActiveAnimation(screen, pivotPoint, true, false);
	}
}

bool PlayerAnimations::InitAnimations(){

	Animation run(5);
	run.LoadSprite("player-run");
	run.ScaleAnimationSprite(0.9, 0.9);
	run.SetVerticalAlign(AnimVerticalAlign::Bottom);
	mAnimator.AddAnimation("run", run);

	Animation idle(20);
	idle.LoadSprite("player-idle");
	idle.ScaleAnimationSprite(0.9, 0.9);
	idle.SetVerticalAlign(AnimVerticalAlign::Bottom);
	idle.SetLoopTime(false);
	idle.SetNumberOfLoops(5);
	mAnimator.AddAnimation("idle", idle);

	mAnimator.ChangeAnimation("idle");

	return true;
}

bool PlayerAnimations::NewAnimationState(const PlayerState& state){
	if(lastState != state){
		lastState = state;
		return true;
	}
	return false;
}

void PlayerAnimations::SetNewAnimation(){

	switch(lastState){
	case PlayerState::idle:
		mAnimator.ChangeAnimation("idle");
		break;
	case PlayerState::run:
		mAnimator.ChangeAnimation("run");
		break;
	case PlayerState::firstJump:
		break;
	case PlayerState::secondJump:
		break;
	case PlayerState::falling:
		break;
	case PlayerState::freezed:
		break;
	case PlayerState::hitted:
		break;
	}
}
