#ifndef SRC_APP_TIME_H_
#define SRC_APP_TIME_H_

#include <SDL2/SDL.h>
#include <stdint.h>
#include <functional>

using UpdateAction = std::function<void()>;

class Time{
public:

	Time();

	inline void SetFrameRate(uint32_t fps) { frameRate = fps; }

	void UpdateTime(UpdateAction executeFrame);

	float DeltaTime();			// Return time of last frame time in seconds
	float AppTime(); 			// Return time since App have been launched

	inline unsigned int GetActualFrame() const { return frame; }

private:
	uint32_t frameRate;
	unsigned int frame;

	uint32_t lastTickTime;
	uint32_t currentFrameDuration;
	uint32_t prevFrameDuration;

	float timeScale;
};


#endif /* SRC_APP_TIME_H_ */
