#ifndef SRC_GRAPHICS_BMPIMAGE_H_
#define SRC_GRAPHICS_BMPIMAGE_H_

#include <stdint.h>
#include <vector>

#include "Color.h"
#include "AARectangle.h"
#include "Vec2D.h"


struct ImageCanvas{
	AARectangle AARect = AARectangle(Vec2D(0, 0), Vec2D(1.0, 1.0));
	float Rotation = 0;
	Vec2D RotationPoint = Vec2D::Zero;
};

class BMPImage {
public:

	BMPImage();
	bool LoadImage(const std::string& path);

	const std::vector<Color>& GetPixels() const;

	inline uint32_t GetImageWidth() const { return mWidth; }
	inline uint32_t GetImageHeight() const {return mHeight; }

	void ScaleImage(float xScale, float yScale, bool relative=true);

	void RotateAroundLocalPoint(const Vec2D& point, float angle);
	void RotateAroundCenter(float angle);

	void SetHeight(const float& height, bool autoWidth = false);
	void SetWidth(const float& width, bool autoHeight = false);

private:
	uint32_t mWidth, mHeight;
	uint32_t originalWidth, originalHeight;

	std::vector<Color> mOriginalPixels;
	std::vector<Color> mPixels;

	ImageCanvas mCanvas;
};


#endif /* SRC_GRAPHICS_BMPIMAGE_H_ */
