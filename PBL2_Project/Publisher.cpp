#include "publisher.h"
#include "game.h"

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
