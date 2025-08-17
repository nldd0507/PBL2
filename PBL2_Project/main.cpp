#include <iostream>
#include "stack.h"
using namespace std;


class Publisher;

class Game {
public:
	string id;
	string name;
	double price;
	double discount;
	//  string version;
	string genre;
	string ageRating;
	//  Stack<string> reviews;
	//  Stack<float> ratings;
	Publisher* publisher;


	Game(string i, string n, double p, string g, string ar, Publisher* pub)
		:id(i), name(n), price(p), discount(0), genre(g), ageRating(ar), publisher(pub) {
	}
private:
};


class Publisher {
public:
	string id;
	string name;
	double rating;
	Stack<Game*> games;

	Publisher(string i, string n) :id(i), name(n) {
	}

	void addGame(Game* g) {
		games.push(g);
	}

	void printGames() {
		Stack<Game*> tmp = games;
		cout << "Publisher: " << name << endl;
		while (!tmp.isEmpty()) {
			Game* g = tmp.topValue();
			cout << " - " << g->name << " ($" << g->price << ", Genre: " << g->genre << ")" << endl;
			tmp.pop();
		}
	}
private:
};

class User {
public:
	string id;
	string username;
	///string birthday;
	int age;
	double wallet;

	User(string i, string u, int a, double w) : id(i), username(u), age(a), wallet(w) {}

	void addToCart(Game* g) {
		cart.push(g);
	}

	void printCart() {
		Stack<Game*> tmp = cart;
		cout << "User: " << username << " (wallet$" << wallet << ")" << endl;
		cout << "  Cart: " << endl;
		while (!tmp.isEmpty()) {
			Game* g = tmp.topValue();
			cout << "    -" << g->name << " ($" << g->price << ")" << endl;
			tmp.pop();
		}
	}

private:
	Stack<Game*> cart;
};

int main() {
	Publisher* nintendo = new Publisher("P1", "Nintendo");
	Publisher* sony = new Publisher("P2", "Sony Interactive Entertainment");
	Publisher* ubisoft = new Publisher("P3", "Ubisoft");

	// ===== Tao Game =====
	Game* zelda = new Game("G1", "The Legend of Zelda: Breath of the Wild", 59.99, "Action-Adventure", "E10+", nintendo);
	Game* mario = new Game("G2", "Super Mario Odyssey", 49.99, "Platformer", "E10+", nintendo);
	Game* gow = new Game("G3", "God of War", 39.99, "Action", "M", sony);
	Game* acv = new Game("G4", "Assassin's Creed Valhalla", 69.99, "Action RPG", "M", ubisoft);

	// Link game vao publisher
	nintendo->addGame(zelda);
	nintendo->addGame(mario);
	sony->addGame(gow);
	ubisoft->addGame(acv);

	// ===== Tao User =====
	User* alice = new User("U1", "Alice", 22, 100.0);
	User* bob = new User("U2", "Bob", 18, 50.0);

	// Alice them game vao gio
	alice->addToCart(zelda);
	alice->addToCart(acv);

	// Bob them game vao gio
	bob->addToCart(mario);

	// ===== Demo In Ra =====
	nintendo->printGames();
	sony->printGames();
	ubisoft->printGames();

	cout << "\n";
	alice->printCart();
	cout << "\n";
	bob->printCart();

	return 0;
}

