#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <SDL2/SDL.h>
#include <stdint.h>
#include <vector>
#include <cmath>
#include "Utils.h"
#include "Color.h"
#include "Vec2D.h"
#include "ScreenBuffer.h"
#include "Line2D.h"
#include "Shape.h"
#include "Circle.h"


class Screen{
	uint32_t mWidth, mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	void ClearScreen();
public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreens();
	inline void SetClearColor(const Color& color){mClearColor = color;}

	// Getters
	inline uint32_t GetWidth()const{return mWidth;}
	inline uint32_t GetHeight()const{return mHeight;}

	// Draw Methods
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& vec, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const Shape& shape, const Color& color, bool fillShape = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fillShape = false, const Color& fillColor = Color::White());

	void FillPoly(const std::vector<Vec2D>& points, const Color& color);
};


#endif /* GRAPHICS_SCREEN_H_ */
