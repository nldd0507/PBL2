#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"

#include "PublisherManager.h"

//GameManager::~GameManager() {
//	games.clear();
//}
void GameManager::addGame(Game* g) {
	games.push_back(g);
}

void GameManager::printAll() const {
	for (auto p : games) {
		if (p != nullptr) {
			std::cout << *p;
		}
	}
}

void GameManager::importFromFile(const std::string& filename, const PublisherManager& publishers) {
	std::ifstream in(filename);
	if (!in) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, name, pr, genre,ageRating, pubName;
		double price;

		if (std::getline(ss, id, ';')
			&& std::getline(ss, name,';') 
			&& std::getline(ss, pr, ';') 
			&&  std::getline(ss, genre, ';') 
			&& std::getline(ss, ageRating,';')
			&& std::getline(ss,pubName,';'))
		{

			id = utils::formatName(id);
			name = utils::formatName(name);
			price = utils::string_To_Double(pr);
			genre = utils::formatName(genre);
			ageRating = utils::formatName(ageRating);
			pubName = utils::formatName(pubName);

			auto publisher = publishers.getPublisherByName(pubName);
			if (!publisher) {
				std::cerr << "Publisher not found: " << pubName << std::endl;
				continue;
			}
			auto g = std::make_shared<Game>(id, name, price, genre, ageRating, publisher);
			//Game* g = new Game(id, name, price, genre, ageRating, publisher);
			addGame(g.get());
			publisher->addGame(g);
		}

	}
	in.close();
}

void GameManager::exportToFile(const std::string& filename) const {
	std::ofstream out(filename);
	if (!out) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}

	for (auto p : games) {
		if (p != NULL) {
			out << p->getId() << " ; " << p->getName() << " ; " << p->getPrice() << " ; " << p->getGenre() << " ; " << p->getAgeRating()<<" ; " << p->getPublisher()->getName() <<" ; " << std::endl;
		}
	}

	out.close();
	std::cout << "Data exported to " << filename << std::endl;
}


