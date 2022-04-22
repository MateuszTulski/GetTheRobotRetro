#include "BMPImage.h"
#include <stdint.h>
#include <SDL2/SDL.h>
#include "Utils.h"

BMPImage::BMPImage():mWidth(0), mHeight(0), originalWidth(0), originalHeight(0){

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

	originalWidth = mWidth = tempSurface->w;
	originalHeight = mHeight = tempSurface->h;

	bmpSurface = SDL_CreateRGBSurface(0, mWidth, mHeight, 32, rmask, gmask, bmask, amask);

	// Now surface is in RGB format
	// Make copy and remove temp surface

	SDL_BlitSurface(tempSurface,NULL,bmpSurface,NULL);
	SDL_FreeSurface(tempSurface);


	uint32_t lengthOfFile = mWidth * mHeight;

	mOriginalPixels.reserve(lengthOfFile);
	mPixels.reserve(lengthOfFile);

	SDL_LockSurface(bmpSurface);

	uint32_t * pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for(uint32_t i = 0; i < lengthOfFile; ++i)
	{
		Color col;
		col = pixels[i];
		mOriginalPixels.push_back(col);
		mPixels.push_back(col);
	}
	SDL_UnlockSurface(bmpSurface);
	SDL_FreeSurface(bmpSurface);

	return true;
}

const std::vector<Color>& BMPImage::GetPixels() const {
	return mPixels;
}

void BMPImage::ScaleImage(float xScale, float yScale, bool relative){

	uint32_t newWidth, newHeight;
	if(relative)
	{
		newWidth = static_cast<uint32_t>(xScale * mWidth);
		newHeight = static_cast<uint32_t>(yScale * mHeight);
	}
	else
	{
		newWidth = static_cast<uint32_t>(xScale * originalWidth);
		newHeight = static_cast<uint32_t>(yScale * originalHeight);
	}

	float xScaleToOriginal = static_cast<float>(newWidth) / originalWidth;
	float yScaleToOriginal = static_cast<float>(newHeight) / originalHeight;

	std::vector<Color> newImage;

	newImage.reserve(newWidth * newHeight);

	for(uint32_t r = 0; r < newHeight; r++)
	{
		for(uint32_t c = 0; c < newWidth; c++)
		{
			int closestPixelCol = static_cast<int>(static_cast<float>(c) / xScaleToOriginal);
			closestPixelCol = Clamp(closestPixelCol, 0, originalWidth-1);

			int closestPixelRow = static_cast<int>(static_cast<float>(r) / yScaleToOriginal);
			closestPixelRow = Clamp(closestPixelRow, 0, originalHeight-1);

			newImage.push_back(mOriginalPixels.at(GetPixelIndex(closestPixelCol, closestPixelRow, originalWidth)));
		}
	}

	mPixels = newImage;

	mWidth = newWidth;
	mHeight = newHeight;
}

void BMPImage::RotateAroundLocalPoint(const Vec2D& point, float angle){

}

void BMPImage::RotateAroundCenter(float angle){
	RotateAroundLocalPoint(Vec2D(0.5, 0.5), angle);
}

void BMPImage::SetHeight(const float& height, bool autoWidth){



}
void BMPImage::SetWidth(const float& width, bool autoHeight){



}






