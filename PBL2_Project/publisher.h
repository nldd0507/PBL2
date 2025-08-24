#ifndef publisher_h 
#define publisher_h

#include <string>
#include <iostream>
#include <fstream>
//using namespace std; 

class Publisher {
public:
	Publisher(const std::string &id,  const std::string &name);
	//~Publisher();
	const std::string &getId() const;
	const std::string &getName() const;
	
	friend std::ostream& operator << (std::ostream& o, const Publisher& p);

	void saveToFile(std::ofstream& out) const;
private:
	std::string name;
	std::string id;
};


#endif