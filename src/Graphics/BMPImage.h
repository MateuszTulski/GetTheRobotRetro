#ifndef SRC_GRAPHICS_BMPIMAGE_H_
#define SRC_GRAPHICS_BMPIMAGE_H_

#include <stdint.h>
#include <vector>
#include "Color.h"

class BMPImage {
public:

	BMPImage();
	bool LoadImage(const std::string& path);

	inline const std::vector<Color>& GetPixels() const {return mPixels;}
	inline uint32_t GetImageWidth() const {return mWidth;}
	inline uint32_t GetImageHeight() const {return mHeight;}

private:
	uint32_t mWidth;
	uint32_t mHeight;
	std::vector<Color> mPixels;
};


#endif /* SRC_GRAPHICS_BMPIMAGE_H_ */
