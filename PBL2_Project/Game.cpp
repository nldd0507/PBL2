#include <filesystem>
#include "Utils.h"
#include <bits/stdc++.h>
#include "game.h"
#include "publisher.h"

std::vector<Game*> Game::allGames = {};

Game::Game(const std::string &i,
	const std::string &n,
	const double &p,
	const double &d,
	const std::string &g,
	const std::string &ar,
	Publisher *pub)
	: id(i), name(n), price(p), discount(d), genre(g), ageRating(ar), publisher(pub){
	afterDiscount = price * (100 -discount) /100;
	allGames.push_back(this);
	//this->saveGameDetail();
}

Game::~Game() {
	if (!allGames.empty()) {
		auto it = std::remove(allGames.begin(), allGames.end(), this);
		if (it != allGames.end()) {
			allGames.erase(it, allGames.end());
			std::cout << "Removed: " << name << " from Game List." << std::endl;
		}
	}
}


std::ostream& operator <<(std::ostream& o, const Game& g) {
	o << g.id << " | " << g.name << " | " << g.price << " | " << g.discount << " | " << g.afterDiscount << " | " << g.genre << " | " << g.ageRating;
	if (g.publisher) {
		o << " | " << g.publisher->getSortName() << std::endl;
	}
	else o << " | [No Publisher]";
	return o;
}

//Static Method
void Game::addGame() {

}
Game* Game::getGameById(const std::string& id) {
	for (auto* g : allGames) {
		if (g && g->getId() == id) return g;
	}
	return nullptr;
}
bool Game::isExist(const std::string &id) {
	for (auto* g : allGames) {
		if (g && g->getId() == id) return true;
	}
	return false;
}

void Game::printAllGames() {
	std::cout << allGames.size() << std::endl;
	for (auto* g : allGames) {
		std::cout << *g;
	}
}

void Game::loadAllGamesSummary (const std::string& filename) {
	//std::string path = "data/games/" + filename;
	std::string path = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\games\\" + filename;
	std::ifstream in(path);
	if (!in) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}
	std::string line;
	std::getline(in, line);
	while (std::getline(in, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string id, name, price, discount, genre, ageRating, pubName;
		if (std::getline(ss, id, ';')
			&& std::getline(ss, name, ';')
			&& std::getline(ss, price, ';')
			&& std::getline(ss, discount, ';')
			&& std::getline(ss, genre, ';')
			&& std::getline(ss, ageRating, ';')
			&& std::getline(ss, pubName, ';'))
		{

			pubName = utils::formatName(pubName);

			Publisher* publisher = Publisher::getPublisherByName(pubName);

			if (!publisher) {
				std::cerr << "Publisher not found: " << pubName << std::endl;
				continue;
			}

			Game *g = new Game(
				utils::formatName(id),
				utils::formatName(name),
				utils::string_To_Double(price),
				utils::string_To_Double(discount),
				utils::formatName(genre),
				utils::formatName(ageRating),
				publisher);

			publisher->addGame(g);
		}

	}
	in.close();
}

void Game::saveAllGamesSummary(const std::string& filename) {
	std::string path = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\games\\" + filename;
	std::ofstream out(path);
	if (!out) {
		std::cerr << "Cannot open file: " << filename << std::endl;
		return;
	}
	out << "ID;Name;Price;Discount;Genre;AgeRating;Publisher;" << std::endl;
	for (auto* p : allGames) {
		if (p != NULL) {
			out << p->getId() << ";" << p->getName() << ";" << p->getPrice() << ";" << p->getDiscount() << ";" << p->getGenre() << ";" << p->getAgeRating() << ";" << p->getPublisher()->getName() << ";" << std::endl;
		}
	}

	out.close();
	//std::cout << "Data exported to " << filename << std::endl;
}

void Game::saveGameDetail() const {
	std::cout << "Tao vua moi ghi file day cu" << std::endl;
	std::cin.get();

	namespace fs = std::filesystem;

	//std::string dir = "data/games/" + publisher->getId();
	std::string dir = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\games\\" + publisher->getId();
	//std::string path = dir + "/" + id + ".txt";
	std::string path = dir + "\\" + id + ".txt";


	fs::create_directories(dir);

	std::ofstream fout(path);
	if (!fout.is_open()) {
		std::cerr << "Error: cannot write publisher file: " << path << "\n";
		return;
	}

	fout << "id:" << id << "\n";
	fout << "name:" << name << "\n";
	fout << "price:" << price << "\n";
	fout << "discount:" << discount << "\n";
	fout << "genre:" << genre << "\n";
	fout << "ageRating:" << ageRating << "\n";
	fout << "publisher:" << publisher->getName() << "\n";
	fout.close();

	saveAllGamesSummary();
}




