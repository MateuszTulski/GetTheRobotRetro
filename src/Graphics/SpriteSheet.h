#ifndef SRC_GRAPHICS_SPRITESHEET_H_
#define SRC_GRAPHICS_SPRITESHEET_H_

#include "BMPImage.h"
#include "Utils.h"

#include <vector>
#include <functional>


using ReadField = std::function<void(std::string field)>;

struct Sprite{
	uint32_t xPos = 0;
	uint32_t yPos = 0;
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t screenX = 0;
	uint32_t screenY = 0;
	bool flipX = false;
	bool flipY = false;
};

class SpriteSheet {
public:
	SpriteSheet();
	bool LoadSprite(const std::string& name);

	void DrawSprite(Screen& screen, const Vec2D& position, const std::string& name, bool flipHorizontal = false, bool globalPosition = true, const float& rotation=0);
	void DrawSprite(Screen& screen, const Vec2D& position, const std::string& name, colorOverlay overlay, bool flipHorizontal = false, bool globalPosition = true, const float& rotation=0);

	void ScaleSpriteSheet(float xScale, float yScale, bool relative = true);

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
	Scale2D mScale;
};



#endif /* SRC_GRAPHICS_SPRITESHEET_H_ */
