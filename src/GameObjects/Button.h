#ifndef SRC_GAMEOBJECTS_BUTTON_H_
#define SRC_GAMEOBJECTS_BUTTON_H_

#include <string>
#include "AARectangle.h"
#include <functional>
#include "Color.h"
#include "ColorManipulation.h"
#include "BitmapFont.h"

class Screen;

class Button {

public:
	using ButtonAction = std::function<void(void)>;

	Button();
	Button(const BitmapFont& font);
	void InitButton(const Size& buttonSize, const std::string& text, Vec2D position);
	inline void SetButtonAction(const ButtonAction& action) {mAction = action;}

	void Draw(Screen& screen);

	void ExecuteAction();

	inline void SetBaseColor(const Color& color) {mBaseColor.SetModifier(COL_MULTIPLY, color);}
	inline void SetHighlitColor(const Color& color) {mHighlightColor.SetModifier(COL_MULTIPLY, color);}

	void SetButtonActive(const bool& active);
	inline bool IsActive() const {return mIsActive;}

private:
	const BitmapFont mButtonFont;
	AARectangle mAARect;
	std::string mButtonText;
	bool mIsActive;
	ButtonAction mAction;

	ColorManipulation mBaseColor;
	ColorManipulation mHighlightColor;

	Vec2D mTextPosition;
};


#endif /* SRC_GAMEOBJECTS_BUTTON_H_ */
