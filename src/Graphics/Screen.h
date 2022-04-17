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

	// Getters
	inline uint32_t GetWidth()const{return mWidth;}
	inline uint32_t GetHeight()const{return mHeight;}

	AARectangle GetScreenRect() const;

	// Draw Methods
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& vec, const Color& color);
	void Draw(const Line2D& line, const Color& color);
	void Draw(const Shape& shape, const Color& color, bool fillShape = false, const Color& fillColor = Color::White());
	void Draw(const Circle& circle, const Color& color, bool fillShape = false, const Color& fillColor = Color::White());
	void Draw(const BMPImage& image, const Vec2D& position, ColorManipulation& manipulator);
	void Draw(const SpriteSheet& sprite, const std::string& name, const Vec2D& position, ColorManipulation& manipulator);

	void Draw(const BitmapFont& font, const std::string& text, const Vec2D& position);
	void Draw(const BitmapFont& font, const std::string& text, const Vec2D& position, ColorManipulation& manipulator);

	void FillPoly(const std::vector<Vec2D>& points, const Color& color);

private:
	void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& position, ColorManipulation& manipulator);
	Vec2D GetScreenPoint(const Vec2D globalPoint) const;

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

	void ClearScreen();
};


#endif /* GRAPHICS_SCREEN_H_ */
