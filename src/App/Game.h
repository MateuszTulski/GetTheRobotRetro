#ifndef GAMES_GAME_H_
#define GAMES_GAME_H_

#include <stdint.h>
#include <string>

class GameController;
class Screen;

class Game{
public:
	virtual ~Game(){}
	virtual void Init(GameController& controller) = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const std::string& GetSceneName() = 0;
};



#endif /* GAMES_GAME_H_ */
