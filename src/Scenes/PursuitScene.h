#ifndef SRC_SCENES_PURSUITSCENE_H_
#define SRC_SCENES_PURSUITSCENE_H_

#include <memory>

#include "Scene.h"
#include "PursuitController.h"
#include "PhysicsWorld.h"
#include "Player.h"
#include "Robot.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "Button.h"
#include "Platform.h"
#include "LevelLoader.h"
#include "Camera.h"

class PursuitScene : public Scene {
public:
	PursuitScene();
	virtual ~PursuitScene(){};
	void Init() override;
	void Update(uint32_t deltaTime) override;
	void Draw(Screen& screen) override;

	inline void SetGameState(GameState state){mGameState = state;}
	inline const GameState& GetGameState() {return mGameState;}

	const std::string& GetSceneName() const override;
private:
	GameState mGameState;

	Player mPlayer;
	Robot mRobot;
	std::shared_ptr<Camera> mCamera;
	PursuitController mPursuitController;
	UIPanel gameOverPanel;

	LevelLoader mLevelLoader;

	SpriteSheet platformSpriteTemp;
	Platform mPlatform;

	Background mBackground;

	void SetGameControls();

	void LoadLevel();
	void LoadPlayer();
	void LoadRobot();
	void LoadBackground();
	void SetCamera();
	void InitUI();
	void InitGameOverPanel();

	void RestartGame();
};




#endif /* SRC_SCENES_PURSUITSCENE_H_ */
