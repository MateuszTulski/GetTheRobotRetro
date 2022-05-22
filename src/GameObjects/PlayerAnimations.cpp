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
		mAnimator.DrawFlippedActiveAnimation(screen, pivotPoint);
	}
}

bool PlayerAnimations::InitAnimations(){

	Animation run(4);
	run.LoadSprite("player-run");
	run.SetVerticalAlign(AnimVerticalAlign::Bottom);
	mAnimator.AddAnimation("run", run);

	Animation idle(20);
	idle.LoadSprite("player-idle");
	idle.SetVerticalAlign(AnimVerticalAlign::Bottom);
	mAnimator.AddAnimation("idle", idle);

	Animation falling(4);
	falling.LoadSprite("player-falling");
	falling.SetVerticalAlign(AnimVerticalAlign::Bottom);
	falling.SetLoopTime(false);
	mAnimator.AddAnimation("falling", falling);

	Animation jump(4);
	jump.LoadSprite("player-jump");
	jump.SetVerticalAlign(AnimVerticalAlign::Bottom);
	jump.SetLoopTime(false);
	mAnimator.AddAnimation("jump", jump);

	Animation spin(2);
	spin.LoadSprite("player-spin");
	spin.SetVerticalAlign(AnimVerticalAlign::Bottom);
	mAnimator.AddAnimation("spin", spin);

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
		mAnimator.ChangeAnimation("jump");
		break;
	case PlayerState::secondJump:
		mAnimator.ChangeAnimation("spin");
		break;
	case PlayerState::falling:
		mAnimator.ChangeAnimation("falling");
		break;
	case PlayerState::freezed:
		break;
	case PlayerState::hitted:
		break;
	}
}
