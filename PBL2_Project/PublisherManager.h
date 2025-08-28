#ifndef Publisher_manager
#define Publisher_manager

#include "publisher.h"

#include <vector>

class PublisherManager {
private: 
	std::vector<std::shared_ptr<Publisher>> publishers;
public: 
	~PublisherManager() = default;

	int sizePublisherList() const { return publishers.size(); }
	std::shared_ptr<Publisher> getPublisherByName(const std::string& name) const;
	Publisher* getPublisherAt(int index) {
		if (index >= 0 && index < publishers.size()) {
			return publishers[index].get();
		}
		return nullptr;
	}

	void addPublisher(const std::shared_ptr<Publisher>& p);
	void importFromFile(const std::string& file = "publishers.txt");
	void exportToFile(const std::string& file = "publishers.txt") const;
	void printAllPublisher() const;
	void printPub_Games() const;

};

#endif