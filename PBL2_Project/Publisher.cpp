#include "utils.h"

#include "console_utils.h"
#include "publisher.h"
#include "game.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

// STATIC INIT
std::vector<Publisher*> Publisher::allPublishers;

Publisher::Publisher(const std::string& id, const std::string& sN, const std::string& n, const std::string& pw)
    : id(id), sortName(sN), name(n), password(pw) {
    this->savePublisherDetail();
}

Publisher::~Publisher() {
    for (auto* g : gameList)
        if (g) {
            delete g;
        }
    gameList.clear();
    std::cout << "Publisher destroyed" << name << std::endl;
}
void Publisher::showAllGames() {
    for (Game* g : gameList) {
       if(g) std::cout << *g;
    }
}

void Publisher::addGame() {
    std::string id, name, genre, ageRating;
    std::string priceStr, discountStr;
    double price = 0.0, discount = 0.0;

    id = utils::getNewGameId(*this);

    std::cout << "Enter Game Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Price: ";
    std::getline(std::cin, priceStr);
    try {
        price = std::stod(priceStr);
    }
    catch (...) {
        std::cout << "Invalid input for price, defaulting to 0.\n";
    }

    std::cout << "Enter Discount (%): ";
    std::getline(std::cin, discountStr);
    try {
        discount = std::stod(discountStr);
    }
    catch (...) {
        std::cout << "Invalid input for discount, defaulting to 0.\n";
    }

    std::cout << "Enter Genre: ";
    std::getline(std::cin, genre);

    std::cout << "Enter Age Rating: ";
    std::getline(std::cin, ageRating);

    Game* newGame = new Game(id, name, price, discount, genre, ageRating, this);
    gameList.push_back(newGame);
    this->savePublisherDetail();

    Game::saveAllGamesSummary();
    newGame->saveGameDetail();
    //TODO : Them saveGameDetail;
    utils::await(1000); 
    std::cout << "Game \"" << name << "\" added successfully!\n";
}

void Publisher::addGame(Game* g) {
    if (g)
    {
        gameList.push_back(g);
        this->savePublisherDetail();
    }
}

void Publisher::editGame() {
    if (gameList.empty()) {
        std::cout << "Your list is empty!\n";
        return;
    }

    std::cout << "Your games:\n";
    for (auto& g : gameList)
        std::cout << *g;

    std::string id_in;
    std::cout << "Select game ID you want to edit: ";
    std::getline(std::cin, id_in);

    Game* selected = nullptr;
    for (auto& g : gameList) {
        if (g->getId() == id_in) {
            selected = g;
            break;
        }
    }

    if (!selected) {
        std::cout << "Game not found!\n";
        return;
    }

    utils::await(1000, 100);
    std::cout << "Game found!\n" << *selected << "\n";

    std::string menuOptions[6] = {
        "1. Rename",
        "2. Change Price",
        "3. Change Discount",
        "4. Set Genre",
        "5. Set Age Rating",
        "0. Turn Back"
    };

    while (true) {
        c_utils::p_task_menu("Choose your action", menuOptions, 6, 100);

        std::string input;
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        if (input == "1") {
            std::string newName;
            std::cout << "Enter new Name: ";
            std::getline(std::cin, newName);
            selected->setName(utils::formatName(newName));
        }
        else if (input == "2") {
            std::string newPrice;
            std::cout << "Enter new Price: ";
            std::getline(std::cin, newPrice);
            selected->setPrice(std::stod(newPrice));
        }
        else if (input == "3") {
            std::string newDiscount;
            std::cout << "Enter new Discount: ";
            std::getline(std::cin, newDiscount);
            selected->setDiscount(std::stod(newDiscount));
        }
        else if (input == "4") {
            std::string newGenre;
            std::cout << "Enter new Genre: ";
            std::getline(std::cin, newGenre);
            selected->setGenre(utils::formatName(newGenre));
        }
        else if (input == "5") {
            std::string newAgeRating;
            std::cout << "Enter new Age Rating: ";
            std::getline(std::cin, newAgeRating);
            selected->setAgeRating(utils::formatName(newAgeRating));
        }
        else if (input == "0") {
            return;
        }
        else {
            std::cout << "Invalid choice, try again!\n";
            continue;
        }
        Game::saveAllGamesSummary();
        //TODO: Them saveGameDetail cho tung game
        utils::await(1500, 150);
        std::cout << "Change Successfully!\n";
        return;
    }
    //TODO: Chinh lai sao cho hoi co xac nhan doi hay khong
}

void Publisher::deleteGame() {
    if (gameList.empty()) {
        //utils::await();
        std::cout << "No games to delete." << std::endl;
        return;
    }

    showAllGames();
    std::string delId;
    std::cout << "Enter ID of the game to delete: ";
    std::getline(std::cin, delId);

    auto it = std::find_if(gameList.begin(), gameList.end(),
        [&delId](Game* g) { return g->getId() == delId; });

    if (it == gameList.end()) {
        utils::await();
        std::cout << "Game ID not found.\n";
        return;
    }

    Game* g = *it;

    gameList.erase(it);

    auto itAll = std::find(Game::allGames.begin(), Game::allGames.end(), g);
    if (itAll != Game::allGames.end()) {
        Game::allGames.erase(itAll);
    }
    delete g;
    Game::saveAllGamesSummary();
    //TODO : Them xoa file detail
    this->savePublisherDetail();
    utils::await();
    std::cout << "Game deleted successfully.\n";
}

std::ostream& operator<<(std::ostream& o, const Publisher& p) {
    o << "Publisher ID: " << p.id
        << " | Name: " << p.name
        << " | Sort Name: " << p.sortName
        << " | Total Games: " << p.gameList.size();
    return o;
}

// STATIC METHOD
void Publisher::addPublisher(Publisher* p) {
    if (p) allPublishers.push_back(p);
}

Publisher* Publisher::getPublisherByName(const std::string& key) {
    for (auto* p : allPublishers) {
        if (p != nullptr && (p->getSortName() == key || p->getName() == key))
            return p;
    }
    return nullptr;
}

Publisher* Publisher::getPublisherAt(int index) {
    if (index >= 0 && index < (int)allPublishers.size())
        return allPublishers[index];
    return nullptr;
}


void Publisher::printAllPublishers() {
    //std::cout << allPublishers.size() << std::endl;
    for (auto* p : allPublishers)
      if (p)  std::cout << *p << std::endl;
}

void Publisher::printAllWithGames() {
    for (auto* p : allPublishers) {
        if (!p) continue;
        std::cout << *p << std::endl;
        for (auto* g : p->getGames()) {
            std::cout << "  - " << *g << std::endl;
        }
    }
}

void Publisher::loadAllPublishersSummary(const std::string& filename) {
    std::string path = "data/publishers/" + filename;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name, sortName, password;

        if (std::getline(ss, id, ';')
            && std::getline(ss, sortName, ';')
            && std::getline(ss, name, ';')
            && std::getline(ss, password, ';'))
        {
            id = utils::formatName(id);
            sortName = utils::formatName(sortName);
            name = utils::formatName(name);
            password = utils::formatName(password);
            addPublisher(new Publisher(id, sortName, name, password));
        }
    }
    in.close();
}

void Publisher::saveAllPublishersSummary(const std::string& filename) {
    std::string path = "data/publishers/" + filename;
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    out << "ID;Short Name;Name;Password"<<std::endl;
    for (auto* p : allPublishers) {
        if (p) {
            out << p->id << ";" << p->sortName << ";" << p->name <<";" << p->password<<";" << std::endl;
        }
    }

    out.close();
    //std::cout << "Data exported to " << filename << std::endl;
}


void Publisher::clearAll() {
    for (auto* p : allPublishers) {
        if (!p) continue;

        for (auto* g : p->getGames()) {
            if (!g) continue;

            auto& allG = Game::allGames;
            allG.erase(std::remove(allG.begin(), allG.end(), g), allG.end());
            delete g;
            // 5/10 Dieu: Code nay xoa han Node cua vector(Code nay cua chatGPT, Dieu kh hieu ^ ^)

        }

        p->gameList.clear();

        delete p;
    }
    allPublishers.clear();
}

void Publisher::savePublisherDetail() const {
    std::string path = "data/publishers/" + id + ".txt";
    std::ofstream fout(path);
    if (!fout.is_open()) {
        std::cerr << "Error: cannot write publisher file: " << path << "\n";
        return;
    }

    fout << "id:" << id << "\n";
    fout << "sortName:" << sortName << "\n";
    fout << "name:" << name << "\n";
    fout << "password:" << password << "\n";

    fout << "games:";   
    for (auto* game : gameList) {
        fout << game->getId()<<";";
    }
    fout << "\n";
    fout.close(); 
    saveAllPublishersSummary();
}

//Publisher* Publisher::loadFromFile(const std::string& ID) {
//    std::string path = "data/publishers/" + ID + ".txt";
//    std::ifstream fin(path);
//    if (!fin.is_open()) {
//        std::cerr << "Error: publisher file not found: " << path << "\n";
//        return nullptr;
//    }
//
//    std::string id, sortName, pw, pname, line;
//    std::vector<std::string> gameIds;
//
//    while (std::getline(fin, line)) {
//        if (line.rfind("id:", 0) == 0) id = line.substr(3);
//        else if (line.rfind("sortName:", 0) == 0) sortName = line.substr(9);
//        else if (line.rfind("name:", 0) == 0) pname = line.substr(5);
//        else if (line.rfind("password:", 0) == 0) pw = line.substr(9);
//        else if (line.rfind("games:", 0) == 0) {
//            std::string list = line.substr(6);
//            std::stringstream ss(list);
//            std::string g;
//            while (std::getline(ss, g, ',')) {
//                if (!g.empty()) gameIds.push_back(g);
//            }
//        }
//    }
//    fin.close();
//
//    Publisher* p = new Publisher(id, sortName, pname);
//    p->password = pw;
//
//    for (auto& gid : gameIds) {
//        Game* existing = Game::getGameById(gid);
//        if (existing)
//            p->gameList.push_back(existing);
//    }
//
//    return p;
//}

bool Publisher::confirmPassword() {
    std::string input;
    int attempts = 0;

    while (attempts < 3) {
        std::cout << "Enter your password to confirm: ";
        std::getline(std::cin, input);

        if (input == password) {
            std::cout << "Password confirmed.\n";
            return true;
        }
        else {
            attempts++;
            std::cout << "Incorrect password (" << attempts << "/3)\n";
        }
    }

    //std::cout << "Too many failed attempts.Logging out.\n";
    return false;
}

int Publisher::changePassword() {
    std::string oldPass, newPass, confirmPass;
    int attempts = 0;

    while (attempts < 3) {
        std::cout << "Enter current password: ";
        std::getline(std::cin, oldPass);

        if (oldPass == password) {
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPass);

            if (newPass.empty()) {
                std::cout << "Password cannot be empty.\n";
                return 2;
            }

            std::cout << "Confirm new password: ";
            std::getline(std::cin, confirmPass);

            if (newPass != confirmPass) {
                std::cout << "Passwords do not match.\n";
                return 2;
            }

            password = newPass;
            savePublisherDetail();
            std::cout << "Password changed successfully!\n";
            return 1;
        }
        else {
            attempts++;
            std::cout << "Incorrect password (" << attempts << "/3)\n";
        }
    }

    //std::cout << "Too many failed attempts. Logging out...\n";
    return 0; // logout trigger
}


Publisher* Publisher::checkPublisherExist(const std::string &id, const std::string &pw) {
    for (auto* p : allPublishers) {
        if ((p!=nullptr) && (p->id == id) &&(p->password == pw)) return p;
    }
    return nullptr;
}