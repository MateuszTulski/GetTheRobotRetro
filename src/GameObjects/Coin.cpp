#include "Coin.h"
#include "BMPImage.h"

Coin::Coin() : Coin(Vec2D::Zero){
}

Coin::Coin(const Vec2D& position) :	Rigidbody(), isActive(true){
	InitRigidbody(AARectangle(Vec2D::Zero, SIZE), 0, false, true);
	MoveTo(position);
}

void Coin::Draw(Screen& screen, BMPImage& image){
	if(isActive){

		image.DrawImage(screen, GetAARectangle().GetTopLeft(), false, false);
	}
}

void Coin::SetPosition(const Vec2D& position){

}

void Coin::OnCollision(){

}
