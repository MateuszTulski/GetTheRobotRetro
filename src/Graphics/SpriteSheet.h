#ifndef SRC_GRAPHICS_SPRITESHEET_H_
#define SRC_GRAPHICS_SPRITESHEET_H_

#include "BMPImage.h"

#include <vector>
#include <functional>


using ReadField = std::function<void(std::string field)>;

struct Sprite{
	uint32_t xPos = 0;
	uint32_t yPos = 0;
	uint32_t width = 0;
	uint32_t height = 0;
};

class SpriteSheet {
public:
	SpriteSheet();
	bool LoadSprite(const std::string& name);
	Sprite GetSpriteCoordinates(const std::string& name) const;

	std::vector<std::string> GetSpritestNames() const;

	inline const BMPImage& GetImage() const {return mImage;}
	inline uint32_t GetImageWidth() const {return mImage.GetImageWidth();}
	inline uint32_t GetImageHeight() const {return mImage.GetImageHeight();}

private:
	bool LoadSpriteSections(const std::string& path);

	struct SpriteSection{
		std::string key = "";
		Sprite sprite;
	};

	BMPImage mImage;
	std::vector<SpriteSection> mSpriteSections;
	ReadField mReadField = nullptr;
};



#endif /* SRC_GRAPHICS_SPRITESHEET_H_ */
