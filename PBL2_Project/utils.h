#ifndef utils_h
#define utils_h

#include <string>
#include <iomanip>
#include <sstream>
#include "publisher.h"
#include "PublisherManager.h"
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
} 
#endif // !utils_h
