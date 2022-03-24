#ifndef SRC_SCENES_PURSUITSCENE_H_
#define SRC_SCENES_PURSUITSCENE_H_

#include "Scene.h"
#include "PhysicsWorld.h"
#include "Player.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "Button.h"

class PursuitScene : public Scene {
public:
	PursuitScene();
	virtual ~PursuitScene(){};
	void Init() override;
	void Update(uint32_t deltaTime) override;
	void Draw(Screen& screen) override;

	const std::string& GetSceneName() const override;
private:
	Button mTempButton;
	PhysicsWorld world;
	Player mPlayer;
	Rigidbody floor;
	void ResetGame();
};




#endif /* SRC_SCENES_PURSUITSCENE_H_ */
