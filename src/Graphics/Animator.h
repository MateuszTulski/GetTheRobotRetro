#ifndef SRC_GRAPHICS_ANIMATOR_H_
#define SRC_GRAPHICS_ANIMATOR_H_

#include "Animation.h"
#include <vector>
#include <map>
#include <utility>
#include <memory>

class Animator{
public:

	Animator();
	Animator(std::string name, Animation anim);

	void Update();

	void DrawActiveAnimation(Screen& screen, const Vec2D& pivotPoint);
	void DrawFlippedActiveAnimation(Screen& screen, const Vec2D& pivotPoint, bool flipHorizontal, bool flipVertical);

	void AddAnimation(std::string name, Animation anim);
	void ChangeAnimation(const std::string& name, bool immediately = true);


private:
	std::map<std::string, Animation> mAnimations;

	std::string nextAnimation;
	std::string mActiveAnimName;

	std::unique_ptr<Animation> mActiveAnim;

	bool waitForEndOfAnimation;
	void CheckIfAnimationFinished();

	void SetActiveAnimation(const std::string& name);
};



#endif /* SRC_GRAPHICS_ANIMATOR_H_ */
