#include "Animator.h"
#include <algorithm>

Animator::Animator() :
	mActiveAnim(nullptr),
	waitForEndOfAnimation(false){

}

Animator::Animator(std::string name, Animation anim) : mActiveAnimName(name), mActiveAnim(nullptr){
	AddAnimation(name, anim);
	SetActiveAnimation(name);
}

void Animator::Update(){
	if(mActiveAnim!=nullptr){
		mActiveAnim->Update();
	}

	if(waitForEndOfAnimation){
		CheckIfAnimationFinished();
	}
}

void Animator::DrawActiveAnimation(Screen& screen, const Vec2D& pivotPoint){
	mActiveAnim->Draw(screen, pivotPoint);
}

void Animator::DrawFlippedActiveAnimation(Screen& screen, const Vec2D& pivotPoint, bool flipHorizontal){
	mActiveAnim->DrawFlipped(screen, pivotPoint, flipHorizontal);
}

void Animator::AddAnimation(std::string name, Animation anim){
	;
	mAnimations.emplace(std::pair<std::string, Animation>(name, anim));
}

void Animator::ChangeAnimation(const std::string& name, bool immediately){

	if(immediately){
		SetActiveAnimation(name);
	}else{
		nextAnimation = name;
		waitForEndOfAnimation = true;
	}
}

void Animator::CheckIfAnimationFinished(){
	if(!mActiveAnim->IsPlaying()){
		waitForEndOfAnimation = false;
		SetActiveAnimation(nextAnimation);
	}
}

void Animator::SetActiveAnimation(const std::string& name){

	if(mAnimations.size() > 0){
		auto it = find_if(mAnimations.begin(), mAnimations.end(), [&name](std::pair<std::string, Animation> element ){ return element.first == name;});
		if(it != mAnimations.end()){
			mActiveAnim = std::make_unique<Animation>(it->second);
		}

	}
}
