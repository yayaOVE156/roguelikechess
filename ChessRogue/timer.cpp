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

std::chrono::steady_clock::duration Timer::remaining() {
	if (timerActive) {
		return startTime - std::chrono::steady_clock::now();
	}
	else {
		return std::chrono::steady_clock::duration::zero();
	}
}

bool Timer::isActive() const{
	return timerActive;
}

bool Timer::hasExpired(){
	if (timerActive && remaining() <= std::chrono::steady_clock::duration::zero()) {
		stop();
		return true;
	}
	return false;
}