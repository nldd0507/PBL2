#ifndef game_h
#define game_h

#include <string>
#include <memory>
#include <vector>
#include <iostream>
class User;
class Publisher;
class Game {
public:
	friend class User;
	friend class Publisher;

	Game() = default;
	Game(const std::string& i, const std::string& n, const  double& p, const double& d, const std::string& g, const std::string& ar, Publisher* pub);
	~Game();
	//getter
	std::string getId() const { return id; }
	std::string getName() const { return name; }
	double getPrice() const { return price; }
	double getDiscount() const { return discount; }
	std::string getGenre() const { return genre; }
	std::string getAgeRating() const { return ageRating; }
	const Publisher* getPublisher() const { return publisher ; }

	//setter
	void setName(const std::string& n) { name = n; }
	void setPrice(const double& p) { price = p; }
	void setDiscount(const double& d) { discount = d; }
	double getAfterDiscount() const { return afterDiscount; }
	void setGenre(const std::string &g) { genre = g; }
	void setAgeRating(const std::string &ar) { ageRating = ar; }

	friend std::ostream& operator << (std::ostream& o, const Game& g);

	//Static Method
	static void addGame();
	static Game* getGameById(const std::string& id);
	static bool isExist(const std::string &id);
	static void printAllGames();
	static void loadAllGamesSummary(const std::string& filename = "games.txt");
	static void saveAllGamesSummary(const std::string& filename = "games.txt");

	void saveGameDetail() const;
private:

	static std::vector<Game*> allGames;

	std::string id;
	std::string name;
	double price;
	double discount = 0.0;
	double afterDiscount = 0.0;
	//  string version;
	std::string genre;
	std::string ageRating;
	//  Stack<string> reviews;
	//  Stack<float> ratings;
	Publisher* publisher; // cho ni Khanh chua hieu: game chi thuoc 1 Publisher duy nhat thoi chu ? (don gian cho khoe)
	//Note: 05/10 Dieu chinh lai thanh con tro den *publisher
};

#endif
