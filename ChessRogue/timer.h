#ifndef TIMER_H
#define TIMER_H

#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>

class Timer {
private:
	std::chrono::steady_clock::time_point startTime;
	bool timerActive;

public:
	Timer();
	void start();
	void stop();
	std::chrono::steady_clock::duration elapsed();
	bool isActive() const;
	
};
#endif