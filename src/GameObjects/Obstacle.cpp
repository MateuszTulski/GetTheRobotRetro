#include "Obstacle.h"
#include "App.h"

Obstacle::Obstacle() : Obstacle(Vec2D::Zero){
}

Obstacle::Obstacle(const Vec2D& position) : Obstacle(position, DEFAULT_SIZE){
}

Obstacle::Obstacle(const Vec2D& position, const float& size) :
		Rigidbody(),
		isDanger(true),
		isActive(false),
		damage(0),
		disarmedTimer(0){
	damage = DEFAULT_DAMAGE;
	InitRigidbody(AARectangle(Vec2D::Zero, Vec2D(size, size)), 0, false, true);
	MoveTo(position);
}

Obstacle::Obstacle(const Obstacle& other) :
		Rigidbody(),
		isDanger(true),
		isActive(other.isActive),
		damage(other.damage),
		disarmedTimer(0){
	InitRigidbody(other.GetAARectangle(), 0, false, true);
}

bool Obstacle::LoadAnimation(const std::string name){
	if(mAnimation.LoadSprite(name)){
		mAnimation.SetFrameRate(5);
		mAnimation.SetLoopTime(true);

		mAnimation.SetVerticalAlign(AnimVerticalAlign::Center);
		mAnimation.SetHorizontalAlign(AnimHorizontalAlign::Center );

		mAnimation.Play();
		isActive = true;
		return true;
	}
	return false;
}

void Obstacle::Update(){
	UpdateDisarmedTimer();
	mAnimation.Update();
}

void Obstacle::Draw(Screen& screen){
	if(isActive){
//		screen.Draw(GetAARectangle(), Color::Red(), false, Color::Red());
		mAnimation.Draw(screen, GetAARectangle().GetCenterPoint());
	}
}

void Obstacle::SetPosition(const Vec2D& position){

}

int Obstacle::GetDamage(){
	if(!isDanger){
		return 0;
	}

	isDanger = false;
	disarmedTimer = App::Singleton().GetTime().AppTime();

	return damage;
}

void Obstacle::UpdateDisarmedTimer(){
	if(!isDanger){
		if(disarmedTimer+DISARM_AFTER_HIT_TIME < App::Singleton().GetTime().AppTime()){
			isDanger = true;
		}
	}
}





