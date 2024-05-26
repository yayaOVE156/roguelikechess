#ifndef TIMER_H
#define TIMER_H

#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <iomanip>

class Timer {
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::duration duration;
	std::chrono::steady_clock::duration remain;
	bool timerActive;
	bool status;

public:
	Timer();
	void start();
	void start(std::chrono::steady_clock::duration remain);
	void stop();
	void setDuration(std::chrono::steady_clock::duration dur);
	void countDown();
	std::chrono::steady_clock::duration remaining();
	std::chrono::steady_clock::duration remainingTime() {
		return remain;
	}
	std::string remainingTimeString(){
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(remain);
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);



		std::ostringstream oss;
		seconds -= std::chrono::duration_cast<std::chrono::seconds>(minutes);

		oss << std::setw(2) << std::setfill('0') << minutes.count() << ":"
			<< std::setw(2) << std::setfill('0') << seconds.count();
		return oss.str();
	}
	bool isAlive();

	
};


#endif // TIMER_H