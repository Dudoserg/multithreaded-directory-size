#pragma once
#include <iostream>
#include <mutex>
#include <sstream>
#include <ostream>

class PrintInThreads
{
public:
	std::mutex mutex;

	void print(std::stringstream &stream) {
		std::lock_guard<std::mutex> lock(this->mutex);
		std::cout << stream.str();
	}

};

