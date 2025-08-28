#include "PublisherManager.h"
#include "publisher.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "utils.h"
//PublisherManager::~PublisherManager() {
//	for (auto p : publishers) {
//		delete p;
//	}
//	publishers.clear();
//}

void PublisherManager::addPublisher(const std::shared_ptr<Publisher>& p) {
	publishers.push_back(p);
}

std::shared_ptr<Publisher> PublisherManager::getPublisherByName(const std::string& key) const {
	if (key.size() <= 3) {
		for (auto& p : publishers) {
			if (p != nullptr && ( p->getSortName() == key || p->getName()==key)) {
				return p;
			}
		}
	}
	
	return nullptr;
}

void PublisherManager::importFromFile(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, name, sortName;

		if (std::getline(ss, id, ';')
			&& std::getline(ss, sortName, ';')
			&& std::getline(ss, name, ';'))
		{
			id = utils::formatName(id);
			sortName = utils::formatName(sortName);
			name = utils::formatName(name);
			addPublisher(std::make_shared<Publisher>(id, sortName, name));
		}
	}
	in.close();
}
void PublisherManager::exportToFile(const std::string& filename) const {
	std::ofstream out(filename);
	if (!out) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}

	for (auto &p : publishers) {
		if (p != NULL) {
			out << p->getId() << " ; "<<p->getSortName() <<" ; " << p->getName() << std::endl;
		}
	}

	out.close();
	std::cout << "Data exported to " << filename << std::endl;
}

void PublisherManager::printAllPublisher() const {
	for (auto& p : publishers) {
		if (p != nullptr) {
			std::cout << *p;
		}
	}
}

void PublisherManager::printPub_Games() const {
	for (auto p : publishers) {
		std::cout << p->getName() << std::endl;
		
		for (auto q : p->getGames()) {
			std::cout << "     ";
			std::cout << *q;
			std::cout << std::endl;
		}
	}
}

