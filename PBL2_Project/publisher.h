#ifndef publisher_h 
#define publisher_h

#include <vector>
#include <string>
#include <memory>

#include <fstream>
#include <iostream>
//using namespace std; 

class Game;
class Publisher {
public:
	Publisher(const std::string &id, const std::string& sN, const std::string &n, const std::string &pw = "null");
	~Publisher();

	//getter
	std::string getId() const { return id; }
	std::string getName() const { return name; }
	std::string getSortName() const { return sortName; }
	size_t getSizeGameList() const { return gameList.size(); };
	const std::vector<Game*>& getGames() const { return gameList; }
	void showAllGames();

	void addGame();
	void addGame(Game *g);
	void editGame();
	void deleteGame();
	bool changePassword();
	friend std::ostream& operator << (std::ostream& o, const Publisher& p);

	//Static Method (PublisherManager merge)
	static void addPublisher(Publisher* p);
	static Publisher* getPublisherByName(const std::string& name);
	static Publisher* getPublisherAt(int index);
	static void printAllPublishers();
	static void printAllWithGames();
	static Publisher* checkPublisherExist(const std::string& id, const std::string& pw);
	static void loadAllPublishersSummary(const std::string& file = "publishers.txt");
	static void saveAllPublishersSummary(const std::string& file = "publishers.txt");
	static void clearAll(); // Xoa toan han publisher + game cua no

	bool confirmPassword();
	void savePublisherDetail() const;
	//static Publisher* loadFromFile(const std::string& name);
private:
	std::string id;//sau thay thanh user name luon cung duoc
	std::string sortName;
	std::string name;
	std::string password;
	std::vector<Game*> gameList;

	static std::vector<Publisher*> allPublishers;
};



#endif