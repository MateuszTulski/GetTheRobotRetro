#ifndef SRC_UI_UIPANEL_H_
#define SRC_UI_UIPANEL_H_

#include <map>

#include "Vec2D.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "ColorManipulation.h"
#include "UIStatusStripe.h"
#include "UIDynamicText.h"
#include "Button.h"

class Screen;
class BitmapFont;
class Vec2D;


class UIPanel{
public:
	UIPanel();

	void AddStaticImage(const BMPImage& image, const Vec2D& position);
	void AddHPStripe(const UIStatusStripe& stripe);
	void AddDistanceStripe(const UIStatusStripe& stripe);
	void AddTimeText(const UIDynamicText& text);
	void AddScoreText(const UIDynamicText& text);
	void AddRectangleFrame(const AARectangle& frame, const Color& color);
	void AddButton(const Button& button);

	void TriggerActiveButton();
	void ChangeActiveButton(bool moveUp, bool changeBtnReleased);

	inline void SetActive(bool active) { isActive = active; }

	void DrawPanel(Screen& screen);

private:
	bool isActive;
	bool changeBtnReleased;

	std::map<BMPImage, Vec2D> mStaticImages;
	std::vector<std::pair<AARectangle, Color>> mUIFrames;
	std::vector<Button> mButtons;

	UIStatusStripe mPlayerHP, mDistance;
	UIDynamicText timeText, scoreText;

	void DrawStaticImages();

};



#endif /* SRC_UI_UIPANEL_H_ */
