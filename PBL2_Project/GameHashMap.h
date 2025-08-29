#ifndef GameHashMap_H
#define GameHashMap_H

#include "game.h"

#include <string>
#include <memory>
#include <vector>

struct GameEntry {
	std::string key;
	std::shared_ptr<Game> value;
};

class GameHashMap {
private: 
	static const int BUCKET_COUNT = 101;
	std::vector<GameEntry> buckets[BUCKET_COUNT];

	int hash(const std::string& key) const {
		unsigned int h = 0;
		for (int i = 0; i < key.size(); i++){
			h = h * 31 + key[i];
		}
		return h % BUCKET_COUNT;
	}

public:
	void insert(const std::string& key, std::shared_ptr<Game> value){
		int h = hash(key);
		std::vector<GameEntry>& bucket = buckets[h];

		for (auto& entry : buckets[h]) {
			if (entry.key == key) {
				entry.value = value;
				return;
			}
		}
		buckets[h].push_back({ key, value });
	}


	std::shared_ptr<Game> get(const std::string& key) const {
		int h = hash(key);
		for (const auto& entry : buckets[h]) {
			if (entry.key == key) return entry.value;
		}
		return NULL;
	}

	bool isExist(const std::string& key) const {
		return get(key) != NULL;
	}
};


#endif