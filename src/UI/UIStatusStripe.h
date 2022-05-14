#ifndef SRC_UI_UISTATUSSTRIPE_H_
#define SRC_UI_UISTATUSSTRIPE_H_

#include "BMPImage.h"
#include "SpriteSheet.h"
#include <stdint.h>

class Screen;

class UIStatusStripe : public BMPImage{
public:
	using GetValue = std::function<float(void)>;

	UIStatusStripe();
	UIStatusStripe(GetValue val);
	UIStatusStripe(const UIStatusStripe& other);

	UIStatusStripe& operator=(const UIStatusStripe& other);

	void SetCoordinates(uint32_t screenX, uint32_t screenY, bool cropFromLeft);
	inline void SetGetterFunction(GetValue val) {getValueFunc = val;}
	inline void SetOverlayColor(const Color& color) {mOverlayColor = color;}

	void DrawStripe(Screen& screen);

private:
	Sprite mSprite;
	Color mOverlayColor;
	Vec2D mScreenPosition;
	bool mCropSideLeft;		// If false -> Crop from right
	GetValue getValueFunc;

	const bool FLIP_HORIZONTAL = false;
	const bool GLOBAL_POSITION = true;
};



#endif /* SRC_UI_UISTATUSSTRIPE_H_ */
