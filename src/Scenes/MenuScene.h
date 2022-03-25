#ifndef SRC_SCENES_MENUSCENE_H_
#define SRC_SCENES_MENUSCENE_H_

#include <vector>
#include "Scene.h"
#include "Button.h"
#include "Utils.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	void Init() override;
	void Update(uint32_t dt) override;
	void Draw(Screen& theScreen) override;
	const std::string& GetSceneName() const override;

private:
	const Size mButtonSize = {240, 50};
	unsigned int mButtonsSpace = 30;
	std::vector<Button> mButtons;

	unsigned int mActiveButton;
	void NextButton();
	void PrevButton();
	void ResetButtons();
};



#endif /* SRC_SCENES_MENUSCENE_H_ */
