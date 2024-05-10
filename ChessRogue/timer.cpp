#include "timer.h"

Timer::Timer() : timerActive(false) {}

void Timer::start() {
	startTime = std::chrono::steady_clock::now();
	timerActive = true;
}

void Timer::stop() {
	timerActive = false;
}

std::chrono::steady_clock::duration Timer::elapsed() {
	if (timerActive) {
		return std::chrono::steady_clock::now() - startTime;
	}
	else {
		return std::chrono::steady_clock::duration::zero();
	}
}

bool Timer::isActive() const{
	return timerActive;
}