#ifndef SRC_SCENES_GAME_H_
#define SRC_SCENES_GAME_H_

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class Game
{
public:
	virtual ~Game(){}
	virtual void Init(GameController& controller) = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const std::string& GetName() const = 0;
};



#endif /* SRC_SCENES_GAME_H_ */
