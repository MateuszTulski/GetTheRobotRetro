#ifndef SRC_UTILS_ENUMS_H_
#define SRC_UTILS_ENUMS_H_

enum class PlayerState{
	idle = 0,
	run,
	firstJump,
	secondJump,
	falling,
	hitted,
	freezed
};

enum class GameState{
	pursuit = 0,
	pausePanel,
	gameOverPanel
};



#endif /* SRC_UTILS_ENUMS_H_ */
