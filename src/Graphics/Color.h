#ifndef GRAPHICS_COLOR_H_
#define GRAPHICS_COLOR_H_

#include <stdint.h>
#include <iostream>

struct SDL_PixelFormat;

class Color{
public:
	friend std::ostream& operator<<(std::ostream& os, const Color& color);

	static const SDL_PixelFormat* mFormat;
	static void InitColorFormat(const SDL_PixelFormat* format);

	// Color presets
	static Color Black() {return Color(0, 0, 0, 255);}
	static Color White() {return Color(255, 255, 255, 255);}
	static Color Red() {return Color(255, 0, 0, 255);}
	static Color Green() {return Color(0, 255, 0, 255);}
	static Color Blue() {return Color(0, 0, 255, 255);}
	static Color Yellow() {return Color(255, 255, 0, 255);}
	static Color Magenta() {return Color(255, 0, 255, 255);}
	static Color Cyan() {return Color(37, 240, 217, 255);}
	static Color Pink() {return Color(252, 197, 224, 255);}
	static Color Orange() {return Color(245, 190, 100, 255);}

	static Color EvaluateAlphaBlend(const Color& source, const Color& destination);

	Color(): Color(0){}
	Color(uint32_t color): mColor{color}{}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	inline bool operator==(const Color& color) const {return mColor==color.mColor;}
	inline bool operator!=(const Color& color) const {return !(*this==color);}
	inline uint32_t GetPixelColor() const {return mColor;}

	void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void SetRed(uint8_t r);
	void SetGreen(uint8_t g);
	void SetBlue(uint8_t b);
	void SetAlpha(uint8_t a);

	uint8_t GetRed() const;
	uint8_t GetGreen() const;
	uint8_t GetBlue() const;
	uint8_t GetAlpha() const;
private:
	uint32_t mColor;
};


#endif /* GRAPHICS_COLOR_H_ */
