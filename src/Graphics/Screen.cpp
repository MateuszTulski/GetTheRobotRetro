#include <iostream>
#include <cassert>
#include <algorithm>
#include "Screen.h"

Screen::Screen() : mWidth{0}, mHeight{}, moptrWindow{nullptr}, mnoptrWindowSurface{nullptr}{}
Screen::~Screen(){
	assert(moptrWindow);
	if(moptrWindow){
		SDL_DestroyWindow(moptrWindow);
	}
	SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t windowWidth, uint32_t windowHeight, uint32_t mag){
	if(SDL_Init(SDL_INIT_VIDEO)){
		std::cout << "SDL Init failed!" << std::endl;
		return nullptr;
	}
	// Create window
	moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth*mag, windowHeight*mag, 0);

	mWidth = windowWidth;
	mHeight = windowHeight;

	// Check that the window was successfully created
	if (moptrWindow == nullptr) {
		// In the case that the window could not be made...
		std::cout << "Could not create window: %s\n: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	if(moptrWindow){
		mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

		SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
		Color::InitColorFormat(pixelFormat);

		mClearColor = Color::Black();
		mBackBuffer.Init(pixelFormat->format, windowWidth, windowHeight);
		mBackBuffer.Clear(mClearColor);
	}
	return moptrWindow;
}
void Screen::SwapScreens(){
	assert(moptrWindow);
	if(moptrWindow){
		// Clear front screen
		ClearScreen();
		// Copy pixels from back buffer to front
		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);
		SDL_UpdateWindowSurface(moptrWindow);
		// Clear back buffer
		mBackBuffer.Clear(mClearColor);
	}
}
// Draw Methods
void Screen::Draw(int x, int y, const Color& color){

	assert(moptrWindow);
	if(moptrWindow){
		mBackBuffer.SetPixel(color, x, y);
	}
}
void Screen::Draw(const Vec2D& vec, const Color& color){
	assert(moptrWindow);
	if(moptrWindow){
		mBackBuffer.SetPixel(color, vec.GetX(), vec.GetY());
	}
}
void Screen::Draw(const Line2D& line, const Color& color){
	assert(moptrWindow);
	if(moptrWindow){
		int dx, dy;

		int x0 = roundf(line.GetP0().GetX());
		int y0 = roundf(line.GetP0().GetY());
		int x1 = roundf(line.GetP1().GetX());
		int y1 = roundf(line.GetP1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1
		signed const char iy((dy > 0) - (dy < 0));

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x0, y0, color);

		if(dx >= dy){
			//go along in the x

			int d = dy - dx/2;

			while(x0 != x1){
				if(d >= 0){
					d -= dx;
					y0 += iy;
				}

				d += dy;
				x0 += ix;

				Draw(x0, y0, color);
			}
		}else{
			//go along in y
			int d = dx - dy/2;

			while(y0 != y1){
				if(d >= 0){
					d -= dy;
					x0 += ix;
				}

				d += dx;
				y0 += iy;

				Draw(x0, y0, color);
			}
		}
	}
}
void Screen::Draw(const Shape& shape, const Color& color, bool fillShape, const Color& fillColor){

	if(fillShape){
		FillPoly(shape.GetPoints(), fillColor);
	}
	// Number of segments equals number of points
	size_t numberOfLines = shape.GetPoints().size();
	for(size_t i = 0; i < numberOfLines; i++){
		size_t pointA = i;
		size_t pointB = i+1;
		if(pointB==numberOfLines){
			pointB = 0;
		}
		// Create and draw line
		Line2D line(shape.GetPoints()[pointA], shape.GetPoints()[pointB]);
		Draw(line, color);
	}
}
void Screen::Draw(const Circle& circle, const Color& color, bool fillShape, const Color& fillColor){

	unsigned const int numberOfSegments = 30;
	float angle = TWO_PI / static_cast<float>(numberOfSegments);

	Vec2D p0(Vec2D(circle.GetCenterPoint().GetX()+circle.GetRadius(), circle.GetCenterPoint().GetY()));
	Vec2D p1(p0);
	Line2D nextLineToDraw;

	std::vector<Line2D> lines;
	std::vector<Vec2D> points;

	for(unsigned int i = 0; i < numberOfSegments; i++){
		p1.Rotate(angle, circle.GetCenterPoint());

		nextLineToDraw.SetP0(p0);
		nextLineToDraw.SetP1(p1);

		lines.push_back(nextLineToDraw);
		points.push_back(p0);

		p0 = p1;
	}
	// Draw lines
	for(Line2D l : lines){
		Draw(l, color);
	}
	// Fill shape
	if(fillShape){
		FillPoly(points, fillColor);
	}

}

void Screen::FillPoly(const std::vector<Vec2D>& points, const Color& color){
	if(points.size()<=1){
		return;
	}
	// Find shape bounry
	float top {points[0].GetY()};
	float right {points[0].GetX()};
	float bottom {points[0].GetY()};
	float left {points[0].GetX()};

	for(size_t i = 0; i < points.size(); i++){
		if(points[i].GetY() < top){
			top = points[i].GetY();
		}
		if(points[i].GetX() > right){
			right = points[i].GetX();
		}
		if(points[i].GetY() > bottom){
			bottom = points[i].GetY();
		}
		if(points[i].GetX() < left){
			left = points[i].GetX();
		}
	}
	// Scanning lines from top to bottom
	for(int pixelY = top; pixelY < bottom; pixelY++){

		// Check each line of poly shape
		std::vector<float> nodeXVec;
		size_t j = points.size()-1;
		for(size_t i = 0; i < points.size(); i++){

			float pointiY = points[i].GetY();
			float pointjY = points[j].GetY();

			// Check if this line intersect pixelY

			bool checkA = pointiY >= pixelY && pointjY <= pixelY;
			bool checkB = pointjY >= pixelY && pointiY <= pixelY;

			if(checkA || checkB){
				// This line intersects pixelY (horizontal line)
				// Find intersection X
				float sectionHeight = pointjY - pointiY;
				float lineFactor = (pointiY - pixelY) / sectionHeight;

				float pointX = points[i].GetX() + (lineFactor * (points[i].GetX() - points[j].GetX()));

				nodeXVec.push_back(pointX);
			}

			j = i;
		}

		// Sort points (based on x) and draw the line
		std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<float>());

		for(size_t k = 0; k < nodeXVec.size(); k+=2){
			if(nodeXVec[k]>right){
				continue;
			}
			if(nodeXVec[k+1]>left){
				// Bounding left and right site of the line
				if(nodeXVec[k]<left){
					nodeXVec[k] = left;
				}
				if(nodeXVec[k+1]>right){
					nodeXVec[k+1] = right;
				}

				// DRAW each pixel
				for(int pixelX = nodeXVec[k]; pixelX < nodeXVec[k+1]; pixelX++){
					Draw(pixelX, pixelY, color);
				}
			}
		}
	}

}


void Screen::ClearScreen(){
	SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
}
