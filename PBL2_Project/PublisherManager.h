#ifndef Publisher_manager
#define Publisher_manager

#include <vector>
#include "Publisher.h"

class PublisherManager {
private: 
	std::vector<Publisher*> publishers;
public: 
	~PublisherManager();

	void addPublisher(Publisher* p);
	void loadFromFile(const std::string& file="publishers.txt");
	void printAll() const;
};

#endif