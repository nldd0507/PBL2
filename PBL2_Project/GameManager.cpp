#include "utils.h"

#include "GameManager.h"
#include "PublisherManager.h"

#include <sstream>

#include <iostream>
#include <fstream>

//GameManager::~GameManager() {
//	games.clear();
//}
void GameManager::addGame(const std::shared_ptr<Game>& g) {
	games.push_back(g);
	gameMap.insert(g->getId(), g);
}

std::shared_ptr<Game> GameManager::getGameById(const std::string& id) const {
	return gameMap.get(id);
}

bool GameManager::isExist(const std::string& id) const {
	return gameMap.isExist(id);
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
		std::string id, name, price,discount, genre,ageRating, pubName;
		if (std::getline(ss, id, ';')
			&& std::getline(ss, name,';') 
			&& std::getline(ss, price, ';') 
			&& std::getline(ss, discount, ';')
			&& std::getline(ss, genre, ';') 
			&& std::getline(ss, ageRating,';')
			&& std::getline(ss,pubName,';'))
		{

			pubName = utils::formatName(pubName);

			auto publisher = publishers.getPublisherByName(pubName);
			if (!publisher) {
				std::cerr << "Publisher not found: " << pubName << std::endl;
				continue;
			}
			auto g = std::make_shared<Game>(
				utils::formatName(id), 
				utils::formatName(name), 
				utils::string_To_Double(price),
				utils::string_To_Double(discount),
				utils::formatName(genre), 
				utils::formatName(ageRating), 
				publisher);
			//Game* g = new Game(id, name, price, genre, ageRating, publisher);
			addGame(g);
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
			out << p->getId() << " ; " << p->getName() << " ; " << p->getPrice() << " ; "<<p->getDiscount() <<" ; " << p->getGenre() << " ; " << p->getAgeRating() << " ; " << p->getPublisher()->getName() << " ; " << std::endl;
		}
	}

	out.close();
	std::cout << "Data exported to " << filename << std::endl;
}


