#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include <SDL2/SDL.h>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <memory>

#include "Utils.h"
#include "ScreenBuffer.h"
#include "ColorManipulation.h"
#include "Vec2D.h"

struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;

class Line2D;
class Color;
class Shape;
class Circle;
class BMPImage;
class Sprite;
class SpriteSheet;
class AARectangle;
class BitmapFont;
class Camera;

class Screen{
public:
	Screen();
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
	void SwapScreens();
	inline void SetClearColor(const Color& color){mClearColor = color;}

	void SetSceneCamera(std::shared_ptr<Camera> camera);
	void RemoveSceneCamera();

	inline uint32_t GetWidth()const{return mWidth;}
	inline uint32_t GetHeight()const{return mHeight;}

	AARectangle GetScreenRect() const;

	void DrawPixel(int x, int y, const Color& color, bool globalPosition);

	// Draw Shapes
	void Draw(const Vec2D& vec, const Color& color, bool globalPosition = true);
	void Draw(const Line2D& line, const Color& color, bool globalPosition = true);
	void Draw(const Shape& shape, const Color& color, bool fillShape = false, const Color& fillColor = Color::White(), bool globalPosition = true);
	void Draw(const Circle& circle, const Color& color, bool fillShape = false, const Color& fillColor = Color::White(), bool globalPosition = true);

	void FillPoly(const std::vector<Vec2D>& points, const Color& color, bool globalPosition);

	Vec2D GetScreenPoint(const Vec2D& globalPoint) const;
	Vec2D GetGlobalPoint(const Vec2D& screenPoint) const;

	void InvertNextFrameColor();

private:

	uint32_t mWidth, mHeight;

	std::shared_ptr<Camera> mCamera;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* moptrWindow;
	SDL_Surface* mnoptrWindowSurface;

	SDL_Renderer* mRenderer;
	SDL_PixelFormat* mPixelFormat;
	SDL_Texture* mTexture;
	bool mFast;

	bool invertNextFrame;
	unsigned int invertedFrameNum;

	bool InvertColor();
	void ClearScreen();
};


#endif /* GRAPHICS_SCREEN_H_ */
