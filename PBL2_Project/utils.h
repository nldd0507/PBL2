#ifndef utils_h
#define utils_h

#include "publisher.h"

#include <string>
#include <sstream>

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
namespace utils {
	inline std::string formatName(const std::string& input) {
		std::istringstream iss(input);
		std::string word, result;
		while (iss >> word) {
			if (!result.empty()) result += " ";
			result += word;
		}
		return result;
	}

	inline double string_To_Double(const std::string& str) {
		try {
			return std::stod(str);  
		}
		catch (const std::invalid_argument&) {
			return 0.0;
		}
		catch (const std::out_of_range&) {
			return 0.0;
		}
	}

	inline std::string getNewGameId(const Publisher& p) {
		size_t n = p.getSizeGameList() + 1; 
		std::ostringstream oss;
		oss << p.getSortName() << std::setw(2) << std::setfill('0') << n;
		return oss.str();
	}
	//Rotation await
	inline void await(int durationMs = 2000, int delayMs = 100) {
		const char spinner[] = { '|','/','-','\\' };
		int spinnerSize = 4;
		auto start = std::chrono::steady_clock::now();
		while (true) {
			for (int i = 0; i < spinnerSize; i++) {
				std::cout << "\r" << spinner[i] << std::flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

				auto now = std::chrono::steady_clock::now();
				auto elapsed = std::chrono::duration_cast <std::chrono::milliseconds>(now - start).count();

				if (elapsed >= durationMs) {
					std::cout << "\r " << "\r"; 
					return;
				}
			}
		}
	}
	//Dot animation await
	inline void dotAnimation(const std::string& message, int cycles = 3, int delayMs = 200) {
		using namespace std::chrono_literals;

		std::cout << message;
		std::cout.flush();

		for (int i = 0; i < cycles; ++i) {
			for (int dots = 0; dots <= 3; ++dots) {
				std::cout << "\r" << message;
				for (int j = 0; j < dots; ++j)
					std::cout << '.';
				std::cout << "   ";
				std::cout.flush();

				if (dots == 0) std::this_thread::sleep_for(std::chrono::milliseconds(delayMs * 2));
				else std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
			}
		}

		std::cout << "\r" << message << "...   \n";

	}

} 
#endif // !utils_h
 