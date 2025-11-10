#include "user.h"
#include "game.h"
#include "utils.h"
#include "console_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<User*> User::allUsers;

/*User::User(const string& username, const string& password,
           const string& name, int age, double wallet)
    : username(username), password(password),
      name(name), age(age), wallet(wallet) {}

User::~User() {}*/

// ========== BASIC INFO ==========
void User::getInfo() {
    cout << "-- Fill in user's information --\n";
    cout << "- Username: ";
    getline(cin, username);
    cout << "- Password: ";
    getline(cin, password);
    cout << "- Name: ";
    getline(cin, name);
    cout << "- Age: ";
    cin >> age;
    cin.ignore();
    wallet = 0.0;
}

void User::printInfo() const {
    cout << "=== User Information ===\n";
    cout << "Username: " << username << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Wallet: $" << wallet << "\n";
    cout << "Games in cart: " << cart.size() << "\n";
    cout << "Games owned: " << lib.size() << "\n\n";
}

// ========== MONEY MANAGEMENT ==========
void User::addMoney(double amount) {
    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    wallet += amount;
    cout << "  Notification: Successful transaction!\n";
    cout << "- Transaction Amount: +" << amount << " $\n";
    cout << "- Current Balance: " << wallet << " $\n\n";

    saveUserDetail();
    saveAllUsersSummary();
}

bool User::enoughMoney(const double& priceGame) const {
    return wallet >= priceGame;
}

// ========== CART MANAGEMENT ==========
void User::addToCart(const Game& chosenGame) {
    if (isInCart(chosenGame.name) != -1) {
        cout << "  Notification: Game " << chosenGame.name
             << " is already on your cart!\n";
        return;
    }
    cout << "  Notification: Successfully adding game to cart!\n";
    cart.push_back(chosenGame);
}

int User::isInCart(const string& nameGame) const {
    for (int i = 0; i < (int)cart.size(); ++i)
        if (cart[i].name == nameGame) return i;
    return -1;
}

void User::removeCart(const Game& removeGame) {
    int idRemove = isInCart(removeGame.name);
    if (idRemove != -1) {
        cart.erase(cart.begin() + idRemove);
        cout << "  Notification: Successfully erasing game from cart!\n";
    } else {
        cout << "  Notification: Failed erase game because it doesn't exist in cart!\n";
    }
}

void User::clearCart() {
    cout << "  Warning: This will erase all games from your cart!\n";
    cout << "  Confirm [Y/N]: ";
    char choice; cin >> choice; cin.ignore();
    if (choice == 'Y' || choice == 'y') {
        cart.clear();
        cout << "  All games cleared.\n";
    } else {
        cout << "  Cancelled.\n";
    }
}

void User::printCart() const {
    if (cart.empty()) {
        cout << "  Your cart is empty.\n";
        return;
    }
    for (const auto& g : cart) {
        cout << "  === Game Specs ===\n";
        cout << "ID: " << g.id << "\n";
        cout << "Name: " << g.name << "\n";
        cout << "Price (after discount): " << g.getAfterDiscount() << "\n";
        cout << "Genre: " << g.genre << "\n";
        cout << "Age Rating: " << g.ageRating << "\n\n";
    }
}

// ========== LIBRARY MANAGEMENT ==========
void User::addToLib(const Game& chosenGame) {
    lib.push_back(chosenGame);
    cout << "  Notification: Installed game " << chosenGame.name << " successfully\n";
}

int User::isInLib(const string& nameGame) const {
    for (int i = 0; i < (int)lib.size(); ++i)
        if (lib[i].name == nameGame) return i;
    return -1;
}

void User::uninstallGame(const Game& chosenGame) {
    int idUninstall = isInLib(chosenGame.name);
    if (idUninstall != -1) {
        lib.erase(lib.begin() + idUninstall);
        cout << "  Notification: Uninstall game " << chosenGame.name << " successfully!\n";
    } else {
        cout << "  Notification: Game not found in your library!\n";
    }
}

void User::printLib() const {
    if (lib.empty()) {
        cout << "  Your library is empty.\n";
        return;
    }
    cout << "  === Game library of " << name << " ===\n";
    for (const auto& g : lib) {
        cout << "  === Game Specs ===\n";
        cout << "ID: " << g.id << "\n";
        cout << "Name: " << g.name << "\n";
        cout << "Genre: " << g.genre << "\n";
        cout << "Age Rating: " << g.ageRating << "\n\n";
    }
}

// ========== FILE HANDLING ==========
void User::saveUserDetail() const {
    string path = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\users\\" + username + ".txt";
    ofstream fout(path);
    if (!fout.is_open()) {
        cerr << "Error: cannot write user file: " << path << "\n";
        return;
    }

    fout << "username:" << username << "\n";
    fout << "password:" << password << "\n";
    fout << "name:" << name << "\n";
    fout << "age:" << age << "\n";

    fout << "cart:";
    for (size_t i = 0; i < cart.size(); ++i) {
        fout << cart[i].id;
        if (i + 1 < cart.size()) fout << ",";
    }
    fout << "\n";

    fout << "game:";
    for (size_t i = 0; i < lib.size(); ++i) {
        fout << lib[i].id;
        if (i + 1 < lib.size()) fout << ",";
    }
    fout << "\n";

    fout << "wallet:" << wallet << "\n";
    fout.close();
}

void User::loadAllUsersSummary() {
    std::string path = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\users\\users.txt";
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open users summary file.\n";
        return;
    }

    std::string line;
    getline(in, line); // skip header line (username;password;name;age;cart;game;wallet)

    // === helper lambda to trim space + \r ===
    auto trim = [](std::string &s) {
        while (!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\t')) s.pop_back();
        while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) s.erase(s.begin());
    };

    while (getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);

        std::string username, password, name, ageStr, cartStr, gameStr, walletStr;
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, name, ';');
        getline(ss, ageStr, ';');
        getline(ss, cartStr, ';');
        getline(ss, gameStr, ';');
        getline(ss, walletStr, ';');

        trim(username);
        trim(password);
        trim(name);
        trim(ageStr);
        trim(cartStr);
        trim(gameStr);
        trim(walletStr);

        int age = ageStr.empty() ? 0 : stoi(ageStr);
        double wallet = walletStr.empty() ? 0.0 : stod(walletStr);

        User* u = new User(username, password, name, age, wallet);

        // Parse cart (EA1,SE1,...)
        std::stringstream cartSS(cartStr);
        std::string item;
        while (getline(cartSS, item, ',')) {
            trim(item);
            if (!item.empty()) u->cartIds.push_back(item);
        }

        // Parse owned games (SE1,UB1,...)
        std::stringstream gameSS(gameStr);
        while (getline(gameSS, item, ',')) {
            trim(item);
            if (!item.empty()) u->libIds.push_back(item);
        }

        allUsers.push_back(u);
    }

    in.close();
}

void User::saveAllUsersSummary() {
    string path = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\users\\users.txt";
    ofstream out(path);
    if (!out.is_open()) {
        cerr << "Error: cannot write users summary file.\n";
        return;
    }

    out << "username;password;name;age;cart;game;wallet\n";
    for (auto* u : allUsers) {
        if (!u) continue;
        out << u->username << ";"
            << u->password << ";"
            << u->name << ";"
            << u->age << ";";

        // cart
        for (size_t i = 0; i < u->cart.size(); ++i) {
            out << u->cart[i].id;
            if (i + 1 < u->cart.size()) out << ",";
        }
        out << ";";

        // games
        for (size_t i = 0; i < u->lib.size(); ++i) {
            out << u->lib[i].id;
            if (i + 1 < u->lib.size()) out << ",";
        }
        out << ";";

        out << u->wallet << "\n";
    }
    out.close();
}


User* User::checkUserExist(const string& username, const string& password) {
    for (auto* u : allUsers) {
        if (u && u->username == username && u->password == password)
            return u;
    }
    return nullptr;
}

bool User::confirmPassword() {
    string input;
    int attempts = 0;
    while (attempts < 3) {
        cout << "Enter your password to confirm: ";
        getline(cin, input);
        if (input == password) {
            cout << "Password confirmed.\n";
            return true;
        } else {
            attempts++;
            cout << "Incorrect password (" << attempts << "/3)\n";
        }
    }
    return false;
}
