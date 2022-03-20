#include "Shape.h"

void Shape::MoveBy(const Vec2D& offset){
	for(Vec2D& point : mPoints){
		point = point + offset;
	}
}
