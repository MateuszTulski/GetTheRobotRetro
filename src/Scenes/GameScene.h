#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "Scene.h"
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
//	std::unique_ptr<Game> mGame;
};

#endif /* SCENES_GAMESCENE_H_ */
