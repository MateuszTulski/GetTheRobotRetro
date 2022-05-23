#ifndef SRC_GRAPHICS_BACKGROUND_H_
#define SRC_GRAPHICS_BACKGROUND_H_

#include <string>
#include "BMPImage.h"
#include "Vec2D.h"

class Camera;
class Screen;

class Background{
public:
	Background();

	bool InitBackground(const std::string& name);

	void Update(const Camera& camera);
	void Draw(Screen& screen);

	void SetRepeat(bool horizontal, bool vertical);

private:
	BMPImage mImage;

	Vec2D mPosition;		// TOP LEFT CORNER
	Vec2D lastCamPosition;

	bool repeatHorizontal, repeatVertical;

	const float START_Y_POS = 60;
	const uint32_t OPACITY = 120;

	Vec2D GetTextureCoordinates(int globalX, int globalY) const;
};



#endif /* SRC_GRAPHICS_BACKGROUND_H_ */
