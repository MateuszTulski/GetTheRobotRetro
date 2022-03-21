#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "Scene.h"
#include "PhysicsWorld.h"
#include "Player.h"
#include <memory>

class GameScene : public Scene{
public:
	GameScene();
	virtual ~GameScene(){};
	void Init() override;
	void Update(uint32_t deltaTime) override;
	void Draw(Screen& screen) override;

	const std::string& GetSceneName() const override;
private:
	PhysicsWorld world;
	Player mPlayer;
	Rigidbody floor;
	void ResetGame();
};

#endif /* SCENES_GAMESCENE_H_ */
