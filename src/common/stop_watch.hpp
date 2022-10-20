#pragma once
#ifndef __STOP_WATCH_HPP__
#define __STOP_WATCH_HPP__

#pragma once

#include <chrono>
class stop_watch
{
public:
	stop_watch() {}

	void start()
	{
		if (!running)
		{
			begin_time_ = std::chrono::steady_clock::now();
			running = true;
		}
	}

	void stop()
	{
		if (running)
		{
			end_time_ = std::chrono::steady_clock::now();
			elapsed_ = end_time_ - begin_time_;
			running = false;
		}
	}

	void restart()
	{
		elapsed_ = std::chrono::steady_clock::duration::zero();
		begin_time_ = std::chrono::steady_clock::now();
		running = true;
	}

	//√Î
	double elapsed_second()
	{
		return ((double)std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_).count() / 1e3);
	}
	//∫¡√Î
	double elapsed_ms()
	{
		return ((double)std::chrono::duration_cast<std::chrono::microseconds>(elapsed_).count() / 1e3);
	}

protected:
	std::chrono::steady_clock::duration elapsed_ = std::chrono::steady_clock::duration::zero();
	std::chrono::steady_clock::time_point begin_time_;
	std::chrono::steady_clock::time_point end_time_;
	bool running = false;
};


/*
example :
stop_watch watch;
watch.start();
...
watch.stop();
std::cout << watch.elapsed_second() << "s" << std::endl;
*/
#endif