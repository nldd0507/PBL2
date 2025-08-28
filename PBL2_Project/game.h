#ifndef game_h
#define game_h

#include <string>
#include <memory>

class Publisher;
class Game {
public:
	Game() = default;
	Game(const std::string &i, const std::string &n,const  double &p, const double &d, const std::string &g, const std::string &ar, std::shared_ptr<Publisher> pub);

	std::string getName() const { return name; }
	std::string getId() const { return id; }
	double getDiscount() const { return discount; }
	double getPrice() const { return price; }
	std::string getGenre() const { return genre; }
	std::string getAgeRating() const { return ageRating; }
	std::shared_ptr<Publisher> getPublisher() const { return publisher.lock(); }

	friend std::ostream& operator << (std::ostream& o, const Game& g);
private:
	std::string id;
	std::string name;
	double price;
	double discount = 0;
	double afterDiscount;
	//  string version;
	std::string genre;
	std::string ageRating;
	//  Stack<string> reviews;
	//  Stack<float> ratings;
	std::weak_ptr<Publisher> publisher;
};

#endif