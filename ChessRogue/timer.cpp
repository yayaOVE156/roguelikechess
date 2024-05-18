#include "timer.h"

Timer::Timer() : timerActive(false) {}

void Timer::start() {
	startTime = std::chrono::steady_clock::now() + duration;
	timerActive = true;
}

void Timer::start(std::chrono::steady_clock::duration remain) {
	startTime = std::chrono::steady_clock::now() + remain;
	timerActive = true;
}

void Timer::stop() {
	remain = remaining();
	timerActive = false;
}

void Timer::setDuration(std::chrono::steady_clock::duration dur)
{
	duration = dur;
	remain = dur;
}

void Timer::countDown() {
	if (isAlive()) {
		remain = startTime - std::chrono::steady_clock::now();
	}
}

std::chrono::steady_clock::duration Timer::remaining() {
	if (timerActive && isAlive()) {
		return remain;
	}
	else {
		return std::chrono::steady_clock::duration::zero();
	}
}


bool Timer::isAlive() {
	if (remainingTime() >= std::chrono::steady_clock::duration::zero())
		return true;
	else return false;
}