#ifndef SRC_UI_UIDYNAMICTEXT_H_
#define SRC_UI_UIDYNAMICTEXT_H_

#include "BitmapFont.h"
#include <string>
#include <functional>


class UIDynamicText : public BitmapFont{
public:
	using GetValue = std::function<std::string(void)>;

	UIDynamicText();
	UIDynamicText(GetValue val);
	UIDynamicText(const UIDynamicText& other);

	UIDynamicText& operator=(const UIDynamicText& other);

	void SetScreenPosition(uint32_t screenX, uint32_t screenY);

	inline void SetGetterFunction(GetValue val) {getValueFunc = val;}
	inline void SetOverlayColor(const Color& color) {mOverlayColor = color;}

	void DrawDynamicText(Screen& screen);

private:
	Color mOverlayColor;
	Vec2D mScreenPosition;
	GetValue getValueFunc;

	std::string activeText;
	Size textSize;

	void UpdateText(const std::string& text);

	const bool FLIP_HORIZONTAL = false;
	const bool GLOBAL_POSITION = false;
	const FontVerticalAlign VERTICAL_ALIGN = FVA_Middle;
	const FontHorizontalAlign HORIZONTAL_ALIGN = FHA_Center;
};



#endif /* SRC_UI_UIDYNAMICTEXT_H_ */
