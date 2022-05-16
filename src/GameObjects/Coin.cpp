#include "Coin.h"
#include "BMPImage.h"

Coin::Coin() : Coin(Vec2D::Zero){
}

Coin::Coin(const Vec2D& position) :	Rigidbody(), isActive(true){
	InitRigidbody(AARectangle(Vec2D::Zero, SIZE), 0, false, true);
	MoveTo(position);
}

Coin::Coin(const Coin& other) :
		Rigidbody(other),
		isActive(other.isActive){
	MoveTo(other.GetAARectangle().GetTopLeft());
}

void Coin::Draw(Screen& screen, BMPImage& image) const{
	if(isActive){
		image.DrawImage(screen, GetAARectangle().GetTopLeft());
	}
}

void Coin::SetPosition(const Vec2D& position){

}

void Coin::SetActive(bool active){
	isActive = active;
	SetCollider(active);
}
