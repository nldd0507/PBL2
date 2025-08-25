#include <iostream>
#include <memory>
#include "PublisherManager.h"
#include "GameManager.h"

int main() {
    PublisherManager publishers;
    GameManager games;

    publishers.importFromFile("publishers.txt");
    std::cout << "=== Publishers ===" << std::endl;
    publishers.printAll();


    games.importFromFile("games.txt", publishers);
    std::cout << "\n=== Games ===" << std::endl;
    games.printAll();


    //Publisher* p = publishers.getPublisherAt(0);
    //if (p) {
    //    std::cout << "\nPublisher at index 0: " << p->getName() << std::endl;
    //}


    //auto publisher_ptr = publishers.getPublisherByName("NINT"); 
    //if (publisher_ptr) {
    //    auto newGame = std::make_shared<Game>(
    //        "N03",          // id
    //        "EldenRing",    // name
    //        69.99,          // price
    //        "RPG",          // genre
    //        "18+",          // ageRating
    //        publisher_ptr   // Publisher
    //    );
    //    games.addGame(newGame.get());
    //    publisher_ptr->addGame(newGame);

    //    std::cout << "\nAfter adding new game:" << std::endl;
    //    games.printAll();
    //}
    //else {
    //    std::cerr << "Publisher NINT not found!" << std::endl;
    //}

    return 0;
}
