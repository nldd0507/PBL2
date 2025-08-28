#ifndef GameManager_h
#define GameManager_h

#include "game.h"
#include "PublisherManager.h"

#include <vector>

class GameManager {
private:
	std::vector<Game*> games;
public:
	~GameManager() = default;

	void addGame(Game* g);
	void importFromFile(const std::string& file = "games.txt",const PublisherManager& publishers = PublisherManager());
	void exportToFile(const std::string& file = "games.txt") const ;
	void printAll()const;
};

#endif