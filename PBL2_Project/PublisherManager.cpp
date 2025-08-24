#include "PublisherManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

PublisherManager::~PublisherManager() {
	for (auto p : publishers) {
		delete p;
	}
	publishers.clear();
}
void PublisherManager::addPublisher(Publisher* p) {
	publishers.push_back(p);
}

void PublisherManager::printAll() const {
	for (auto p : publishers) {
		if (p != nullptr) {
			std::cout << *p;
		}
	}
}

void PublisherManager::loadFromFile(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, name;

		if (std::getline(ss, id, ';') && std::getline(ss, name)) {
			Publisher* p = new Publisher(id, name);
			addPublisher(p);
		}
	}
	in.close();
}


