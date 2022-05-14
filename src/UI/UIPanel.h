#ifndef SRC_UI_UIPANEL_H_
#define SRC_UI_UIPANEL_H_

#include <map>
#include <functional>

#include "Vec2D.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "ColorManipulation.h"

class Screen;
class BitmapFont;
class Vec2D;

using GetText = std::function<std::string() const>;

class UIPanel{
public:
	UIPanel();

	void AddStaticImage(const BMPImage& image, const Vec2D& position);
	void AddText(const BitmapFont& font, const Vec2D& position, const GetText& text);

	inline void SetActive(bool active) { isActive = active; }

	void DrawPanel(Screen& screen);

private:
	bool isActive;
	std::map<BMPImage, Vec2D> mImages;
	std::map<BitmapFont, Vec2D> mTexts;

	void DrawStaticImages();

};



#endif /* SRC_UI_UIPANEL_H_ */
