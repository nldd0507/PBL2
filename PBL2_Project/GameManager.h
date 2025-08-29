#ifndef GameManager_h
#define GameManager_h

#include "game.h"
#include "PublisherManager.h"
#include "GameHashMap.h"

#include <vector>
#include <string>
#include <memory>

class GameManager {
private:
	std::vector<std::shared_ptr<Game>> games;
	GameHashMap gameMap;

public:
	~GameManager() = default;

	void addGame(const std::shared_ptr<Game> &g);

	bool isExist(const std::string& key) const;
	std::shared_ptr<Game> getGameById(const std::string& id) const;
	void printAll()const;

	void importFromFile(const std::string& file = "games.txt",const PublisherManager& publishers = PublisherManager());
	void exportToFile(const std::string& file = "games.txt") const ;
};

#endif