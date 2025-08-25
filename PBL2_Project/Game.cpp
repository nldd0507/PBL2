#include "game.h"
#include "Utils.h"
#include "publisher.h"

Game::Game(const std::string &i,
	const std::string &n,
	const double &p,
	const std::string &g,
	const std::string &ar,
	std::shared_ptr<Publisher> pub) 
{
	id = i;
	name = n;
	price = p;
	genre = g;
	ageRating = ar;
	publisher = pub;
}
std::ostream& operator <<(std::ostream& o, const Game& g) {
	if (auto pub = g.publisher.lock()) {  
		o << g.id << " " << g.name << " " << g.price
			<< " " << g.genre << " " << g.ageRating
			<< " " << pub->getSortName() << std::endl;
	}
	else {
		o << g.id << " " << g.name << " " << g.price
			<< " " << g.genre << " " << g.ageRating
			<< " [No Publisher]" << std::endl;
	}
	return o;
}
