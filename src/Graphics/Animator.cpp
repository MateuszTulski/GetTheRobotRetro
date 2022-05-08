#include "Animator.h"
#include <algorithm>

Animator::Animator() : mActiveAnim(nullptr){

}

Animator::Animator(std::string name, Animation anim) : mActiveAnimName(name), mActiveAnim(nullptr){
	AddAnimation(name, anim);
	SetActiveAnimation(name);
}

void Animator::Update(){
	if(mActiveAnim!=nullptr){
		mActiveAnim->Update();
	}
}

void Animator::DrawActiveAnimation(Screen& screen, const Vec2D& pivotPoint){
	mActiveAnim->Draw(screen, pivotPoint);
}

void Animator::DrawFlippedActiveAnimation(Screen& screen, const Vec2D& pivotPoint, bool flipHorizontal, bool flipVertical){
	mActiveAnim->DrawFlipped(screen, pivotPoint, flipHorizontal, flipVertical);
}

void Animator::AddAnimation(std::string name, Animation anim){
	;
	mAnimations.emplace(std::pair<std::string, Animation>(name, anim));
}

void Animator::SetActiveAnimation(const std::string& name){

	if(mAnimations.size() > 0){

		auto it = find_if(mAnimations.begin(), mAnimations.end(), [&name](std::pair<std::string, Animation> element ){ return element.first == name;});
		if(it != mAnimations.end()){
			mActiveAnim = std::make_unique<Animation>(std::move(it->second));
		}

	}
}
