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

	void SetButtonColors(const Color& base, const Color& highlighted, const Color& baseText, const Color& highlightedText);

	void SetHighlitColor(const Color& color);

	inline std::string GetButtonName() const { return mButtonText;}

	void SetButtonActive(const bool& active);
	inline bool IsActive() const {return mIsActive;}

private:
	BitmapFont mButtonFont;
	AARectangle mAARect;
	std::string mButtonText;
	bool mIsActive;
	ButtonAction mAction;

	Color buttonBase, buttonHighlighted, baseText, highlightedText;

	Vec2D mTextPosition;
};


#endif /* SRC_GAMEOBJECTS_BUTTON_H_ */
