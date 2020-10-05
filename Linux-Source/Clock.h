#pragma once
#include <SDL2/SDL.h>

#define MICROSECONDS_TO_SECONDS 0.000001f

class Clock
{
public:

	Uint64 cpuTickMostRecent;
	Uint64 deltaMicroseconds;
	Uint64 deltaMicrosecondsUnscaled;
	Uint64 elapsedMicroseconds;
	Uint64 elapsedMicrosecondsUnscaled;
	float deltaSeconds;
	float deltaSecondsUnscaled;
	float elapsedSeconds;
	float elapsedSecondsUnscaled;
	float timeScale;
	
	
	//COnstructor
	inline Clock()
	{
		cpuTickMostRecent = 0L;
		deltaMicroseconds = 0L;
		deltaSeconds = 0.0f;
		elapsedMicroseconds = 0L;
		elapsedSeconds = 0.0f;

		cpuTickMostRecent = 0L;
		deltaMicrosecondsUnscaled = 0L;
		deltaSecondsUnscaled = 0.0f;
		elapsedMicrosecondsUnscaled = 0L;
		elapsedSecondsUnscaled = 0.0f;

		timeScale = 1.0f;

	}


	inline void Start()
	{
		if (cpuTickMostRecent == 0L)
		{
			cpuTickMostRecent = SDL_GetPerformanceCounter();
		}
	}


	//Update the clock after some time passed
	inline void Update()
	{
		Uint64 cpuFrequencyCurrent = SDL_GetPerformanceFrequency();
		Uint64 cpuTicksCurrent = SDL_GetPerformanceCounter();

		if (cpuTickMostRecent == 0L)
		{
			Start();
		}

		Uint64 deltaTicks = cpuTicksCurrent - cpuTickMostRecent;
		deltaMicrosecondsUnscaled = (deltaTicks * 1000000) / cpuFrequencyCurrent;
		elapsedMicrosecondsUnscaled += deltaMicroseconds;

		cpuTickMostRecent = cpuTicksCurrent;

		deltaSecondsUnscaled = float(deltaMicrosecondsUnscaled) * MICROSECONDS_TO_SECONDS;
		elapsedSecondsUnscaled = float(elapsedMicrosecondsUnscaled) * MICROSECONDS_TO_SECONDS;

		//time scaling
		deltaMicroseconds = timeScale * deltaMicrosecondsUnscaled;
		elapsedMicroseconds += deltaMicroseconds;

		deltaSeconds = float(deltaMicroseconds) * MICROSECONDS_TO_SECONDS;
		elapsedSeconds = float(elapsedMicroseconds) * MICROSECONDS_TO_SECONDS;


	}
};

