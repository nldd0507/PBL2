#include "utils.h"
#include "publisher.h"
#include "game.h"

#include <vector>
#include <string>

#include <iostream>
class Game;
Publisher::Publisher(const std::string &i, const std::string &sN, const std::string &n) {
	id = i;
	sortName = sN;
	name = n;
}


std::ostream& operator <<(std::ostream& o, const Publisher& p) {
	o << p.id << " " <<p.sortName<<" " << p.name << std::endl;
	return o;
}

void Publisher::addGame(const std::shared_ptr<Game>&g) {
	gameList.push_back(g);
}

void Publisher::editGame() {
	if (gameList.empty()) {
		std::cout << "Your list is empty! " << std::endl;
		return;
	}
	std::cout << "Your games: " << std::endl;

	for (auto& p : gameList) {
		std::cout << *p;
	}

	std::string id_in;
	std::cout << "Select game ID you want to edit: ";
	getline(std::cin, id_in);
	for (auto& p : gameList) {
		if (p->getId() == id_in) {

			utils::await(1000, 100);
			std::cout << "Game founded!..." << std::endl;
			std::cout << *p;

			std::cout << "Choose your action: " << std::endl;
			std::string menuOptions[6] = {
				"1. Rename",
				"2. Change Price",
				"3. Change Discount",
				"4. Set Genre",
				"5. Set Age Rating",
				"0. Turn Back"
			};

			for (int i = 0; i < 6; i++) {
				std::cout << menuOptions[i] << std::endl;
			}

			int n;
			std::cin >> n;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // <-- Thêm ignore

			while (true) {
				switch (n) {
				case 1: {
					std::cout << "Enter new Name: ";
					std::string newName;
					getline(std::cin, newName);
					p->setName(utils::formatName(newName));
					utils::await(1500, 150);
					std::cout << "Change Successfully!" << std::endl;
					return;
				}
				case 2: {
					std::cout << "Enter new Price: ";
					double newPrice;
					std::cin >> newPrice;
					p->setPrice(newPrice);
					utils::await(1500, 150);
					std::cout << "Change Successfully!" << std::endl;
					return;
				}
				case 3: {
					std::cout << "Enter new Discount: ";
					double newDiscount;
					std::cin >> newDiscount;
					p->setDiscount(newDiscount);
					utils::await(1500, 150);
					std::cout << "Change Successfully!" << std::endl;
					return;
				}
				case 4: {
					std::cout << "Enter new Genre: ";
					std::string newGenre;
					getline(std::cin, newGenre);
					p->setGenre(utils::formatName(newGenre));
					utils::await(1500, 150);
					std::cout << "Change Successfully!" << std::endl;
					return;
				}
				case 5: {
					std::cout << "Enter new Age Rating: ";
					std::string newAgeRating;
					getline(std::cin, newAgeRating);
					p->setAgeRating(utils::formatName(newAgeRating));
					utils::await(1500, 150);
					std::cout << "Change Successfully!" << std::endl;
					return;
				}
				case 0: {
					return;
				}
				default:
					std::cout << "Invalid choice, try again!" << std::endl;
					break;
				}
			}
		}
	}
	std::cout << "Game not found!" << std::endl;
}