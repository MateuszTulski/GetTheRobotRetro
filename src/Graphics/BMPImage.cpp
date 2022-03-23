#include "BMPImage.h"
#include <stdint.h>
#include <SDL2/SDL.h>

BMPImage::BMPImage():mWidth(0), mHeight(0){

}

bool BMPImage::LoadImage(const std::string& path){

	SDL_Surface *tempSurface = SDL_LoadBMP(path.c_str());
	SDL_Surface *bmpSurface;
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	 * on the endianness (byte order) of the machine */

	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
	else
	{
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	}


	if(tempSurface == nullptr)
	{
		return false;
	}

	mWidth = tempSurface->w;
	mHeight = tempSurface->h;

	bmpSurface = SDL_CreateRGBSurface(0, mWidth, mHeight, 32, rmask, gmask, bmask, amask);

	// Now surface is in RGB format
	// Make copy and remove temp surface

	SDL_BlitSurface(tempSurface,NULL,bmpSurface,NULL);
	SDL_FreeSurface(tempSurface);


	uint32_t lengthOfFile = mWidth * mHeight;

	mPixels.reserve(lengthOfFile);

	SDL_LockSurface(bmpSurface);

	uint32_t * pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for(uint32_t i = 0; i < lengthOfFile; ++i)
	{
		Color col;
		col = pixels[i];
		mPixels.push_back(col);
	}
	SDL_UnlockSurface(bmpSurface);
	SDL_FreeSurface(bmpSurface);

	return true;
}
