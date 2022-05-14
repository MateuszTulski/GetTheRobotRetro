#ifndef SRC_UI_UIPANEL_H_
#define SRC_UI_UIPANEL_H_

#include <map>

#include "Vec2D.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "ColorManipulation.h"
#include "UIStatusStripe.h"

class Screen;
class BitmapFont;
class Vec2D;


class UIPanel{
public:
	UIPanel();

	void AddStaticImage(const BMPImage& image, const Vec2D& position);
	void AddHPStripe(const UIStatusStripe& stripe);
	void AddDistanceStripe(UIStatusStripe stripe);

	inline void SetActive(bool active) { isActive = active; }

	void DrawPanel(Screen& screen);

private:
	bool isActive;

	std::map<BMPImage, Vec2D> mStaticImages;
	UIStatusStripe mPlayerHP, mDistance;

	void DrawStaticImages();

};



#endif /* SRC_UI_UIPANEL_H_ */
