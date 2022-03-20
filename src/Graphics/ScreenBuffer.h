#ifndef GRAPHICS_SCREENBUFFER_H_
#define GRAPHICS_SCREENBUFFER_H_

#include <SDL2/SDL.h>
#include <stdint.h>
#include "Color.h"

class ScreenBuffer{
	SDL_Surface * mSurface;
	uint32_t GetIndex(int r, int c);
public:
	ScreenBuffer();
	ScreenBuffer(const ScreenBuffer& screenBuffer);
	~ScreenBuffer();

	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

	void Init(uint32_t format, uint32_t width, uint32_t height);
	inline SDL_Surface* GetSurface(){return mSurface;}

	void Clear(const Color& c = Color::Black());

	void SetPixel(const Color&color, int r, int c);
};

#endif /* GRAPHICS_SCREENBUFFER_H_ */
