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
	std::chrono::steady_clock::duration duration;
	bool timerActive;
	std::chrono::steady_clock::duration remain;

public:
	Timer();
	void start();
	void start(std::chrono::steady_clock::duration remain);
	void stop();
	void setDuration(std::chrono::steady_clock::duration dur);
	std::chrono::steady_clock::duration remaining();
	bool isActive() const;
	bool hasExpired();

	
};
#endif