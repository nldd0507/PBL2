#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include "publisher.h"
#include "PublisherManager.h"
//#include "stack.h"
using namespace std;


//class User {
//public:
//	string id;
//	string username;
//	///string birthday;
//	int age;
//	double wallet;
//
//	User(string i, string u, int a, double w) : id(i), username(u), age(a), wallet(w) {}
//
//	void addToCart(Game* g) {
//		cart.push(g);
//	}
//
//	/*void printCart() {
//		Stack<Game*> tmp = cart;
//		cout << "User: " << username << " (wallet$" << wallet << ")" << endl;
//		cout << "  Cart: " << endl;
//		while (!tmp.isEmpty()) {
//			Game* g = tmp.topValue();
//			cout << "    -" << g->name << " ($" << g->price << ")" << endl;
//			tmp.pop();
//		}
//	}*/
//
//private:
//	/*Stack<Game*> cart;*/
//};

int main() {
	
	PublisherManager publishers;
	publishers.loadFromFile();
	publishers.printAll();

	//// ===== Tao Game =====
	//Game* zelda = new Game("G1", "The Legend of Zelda: Breath of the Wild", 59.99, "Action-Adventure", "E10+", nintendo);
	//Game* mario = new Game("G2", "Super Mario Odyssey", 49.99, "Platformer", "E10+", nintendo);
	//Game* gow = new Game("G3", "God of War", 39.99, "Action", "M", sony);
	//Game* acv = new Game("G4", "Assassin's Creed Valhalla", 69.99, "Action RPG", "M", ubisoft);

	//// Link game vao publisher
	//nintendo->addGame(zelda);
	//nintendo->addGame(mario);
	//sony->addGame(gow);
	//ubisoft->addGame(acv);

	//// ===== Tao User =====
	//User* alice = new User("U1", "Alice", 22, 100.0);
	//User* bob = new User("U2", "Bob", 18, 50.0);

	//// Alice them game vao gio
	//alice->addToCart(zelda);
	//alice->addToCart(acv);

	//// Bob them game vao gio
	//bob->addToCart(mario);

	//// ===== Demo In Ra =====
	//nintendo->printGames();
	//sony->printGames();
	//ubisoft->printGames();

	//cout << "\n";
	//alice->printCart();
	//cout << "\n";
	//bob->printCart();

	return 0;
}

