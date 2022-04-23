#ifndef SRC_GRAPHICS_ANIMATION_H_
#define SRC_GRAPHICS_ANIMATION_H_

#include <vector>

#include "GlobalSettings.h"
#include "SpriteSheet.h"

class Screen;

enum class AnimVerticalAlign{
	Top = 0,
	Center,
	Bottom
};

enum class AnimHorizontalAlign{
	Left = 0,
	Center,
	Right
};

struct AnimationAlignment{
	AnimVerticalAlign vertical = AnimVerticalAlign::Center;
	AnimHorizontalAlign horizontal = AnimHorizontalAlign::Center;
};


class Animation{
public:

	Animation();
	Animation(float fps);
	Animation(const std::string& spriteFileName, float fps = DEFAULT_ANIMATINOS_FPS);

	bool LoadSprite(const std::string& name);

	inline void ScaleAnimationSprite(float xScale, float yScale) { mSpriteSheet.ScaleSpriteSheet(xScale, yScale); }

	void Update(uint32_t deltaTime);
	void Draw(Screen& screen, const Vec2D& pivotPoint);

	inline void SetLoopTime(bool loop) { loopTime = loop; }

	inline void Play() { isPlaying = true; }
	inline void Stop() { isPlaying = false; }

	inline bool IsPlaying() const { return isPlaying; }

	inline size_t GetNumberOfFrames() const { return mFramesNames.size(); }

private:
	SpriteSheet mSpriteSheet;
	AnimationAlignment mAlign;
	std::vector<std::string> mFramesNames;
	unsigned int mActualFrame;
	float mFrameRate;

	bool isPlaying;
	bool loopTime;
	bool playReverse;

	Vec2D GetDrawPosition(const Vec2D& pivotPoint);
};



#endif /* SRC_GRAPHICS_ANIMATION_H_ */
