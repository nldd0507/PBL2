#include <iostream>
#include <memory>
#include "PublisherManager.h"
#include "GameManager.h"
#include "publisher.h"
#include "user.h"
using namespace std;


int main() {
    // Khanh them
    User us;
    us.getInfo();
    us.printInfo();

    PublisherManager publishers;
    GameManager games;


    publishers.importFromFile("publishers.txt");
    Publisher* pub = publishers.getPublisherAt(0);
    games.importFromFile("games.txt", publishers);
    pub->editGame();
    /* std::cout << "=== Publishers ===" << std::endl;
    std::cout << "\n=== Games ===" << std::endl;

    publishers.printPub_Games();*/

    return 0;
}
