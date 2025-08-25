#ifndef publisher_h 
#define publisher_h

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
//using namespace std; 

class Game;
class Publisher : public std::enable_shared_from_this<Publisher>  {
public:
	Publisher(const std::string &id, const std::string& sN, const std::string &n );
	//~Publisher();


	std::string getId() const { return id; }
	std::string getName() const { return name; }
	std::string getSortName() const { return sortName; }
	size_t getSizeGameList() const { return gameList.size(); };

	void addGame(const std::shared_ptr<Game>&g);
	
	friend std::ostream& operator << (std::ostream& o, const Publisher& p);
private:
	std::string name;
	std::string sortName;
	std::string id;
	std::vector<std::shared_ptr<Game>> gameList;
};


#endif