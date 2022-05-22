#ifndef SRC_GRAPHICS_BMPIMAGE_H_
#define SRC_GRAPHICS_BMPIMAGE_H_

#include <stdint.h>
#include <vector>
#include <functional>

#include "Color.h"
#include "AARectangle.h"
#include "Vec2D.h"
#include "ColorManipulation.h"
#include "Screen.h"

class SpriteSheet;

using colorOverlay = std::function<Color(const Color& inputColor)>;

class BMPImage {
public:

	BMPImage();
	bool LoadImage(const std::string& path);
	bool LoadImageFromSpriteSheet(const SpriteSheet& sprite, const std::string name);

	bool operator<(const BMPImage& other) const;

	void DrawImage(Screen& screen, const Vec2D& position, bool flipHorizontal = false, bool globalPosition = true) const;
	void DrawImage(Screen& screen, const Vec2D& position, colorOverlay overlay, bool flipHorizontal = false, bool globalPosition = true) const;
	void DrawImageSprite(Screen& screen, const Vec2D& position, const Sprite& sprite, bool flipHorizontal = false, bool globalPosition = true) const;
	void DrawImageSprite(Screen& screen, const Vec2D& position, const Sprite& sprite, colorOverlay overlay, bool flipHorizontal = false, bool globalPosition = true, const float& rotation = 0);

	const std::vector<Color>& GetPixels() const;

	inline uint32_t GetImageWidth() const { return mWidth; }
	inline uint32_t GetImageHeight() const {return mHeight; }

	inline uint32_t GetOriginalImageWidth() const { return originalWidth; }
	inline uint32_t GetOriginalImageHeight() const { return originalHeight; }

	void PinInamgeToScreen(const Vec2D& position);

	void ScaleImage(float xScale, float yScale, bool relative=true);

	void RotateAroundLocalPoint(const Vec2D& point, float angle);
	void RotateAroundCenter(float angle);
	void FlipImageHorizontal();

	void SetHeight(const float& height, bool autoWidth = false);
	void SetWidth(const float& width, bool autoHeight = false);

protected:
	void DrawImagePixels(Screen& screen, const Vec2D& position, const Sprite& sprite, colorOverlay overlay, bool flipHorizontal=false, bool globalPosition=true, int cropLeft=0, int cropRight=0) const;
	uint32_t mWidth, mHeight;

private:
	uint32_t originalWidth, originalHeight;

	std::vector<Color> mOriginalPixels;
	std::vector<Color> mPixels;

	bool flipHorizontal, flipVertical;

	bool globalPosition;
	Vec2D screenPosition;

	Vec2D pivotNormalized;	// 0,0 is TopLeftCorner --- 1,1 is BottomRightCorner
	float rotation;

	Vec2D GetPivotPoint(const Vec2D& topLeft, float widht, float height) const;
	Vec2D GetRotatedPointPosition(const Vec2D& imageTopLeftPosition, const Vec2D& pixelPosition) const;
};


#endif /* SRC_GRAPHICS_BMPIMAGE_H_ */
