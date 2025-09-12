#include <bits/stdc++.h>
#include "utils.h"
#include "game.h"
#include "GameManager.h"
#include "user.h"
using namespace std;

User::User(int id, const string &name, int age, double wallet) : id(id), name(name), age(age), wallet(wallet) {}

istream &operator >>(istream &in, User &user) {
    in >> user.id;
    in >> user.name;
    in >> user.age;
    in >> user.wallet;
    return in;
}

ostream &operator <<(ostream &out, const User &user) {
    out << "===  User Information ===\n";
    out << "ID: " << user.id << '\n';
    out << "Name: " << user.name << '\n';
    out << "Age: " << user.age << '\n';
    out << "Wallet: $" << user.wallet << '\n';
    out << "Games in cart: " << user.cart.size() << '\n';
    out << "Games owned: " << user.lib.size() << '\n';
    return out;
}

void User::getInfo() {
    cout << "-- Fill in user's information --\n";
    cout << "- ID: "; cin >> id;
    cout << "- Name: "; cin >> name;
    cout << "- Age: "; cin >> age;
    cout << '\n';
    wallet = 0;
}

void User::printInfo() const {
    cout << "===  User Information ===\n";
    cout << "- ID: " << id << '\n';
    cout << "- Name: " << name << '\n';
    cout << "- Age: " << age << '\n';
    cout << "- Wallet: $" << wallet << '\n';
    cout << "- Games in cart: " << cart.size() << '\n';
    cout << "- Games owned: " << lib.size() << '\n';
    cout << '\n';
}

void User::addMoney(double amount) {
    cout << "  Notification:   Successfull transaction!\n";
    cout << "- Transaction Amount: +" << amount << " $\n";
    cout << "- Current Balance: " << wallet << " $\n\n";
}

bool User::enoughMoney(const double &priceGame) const { // tra ve bool roi add vao thu vien
//    if(walllet >= priceGame) {
//        cout << "   Succesfully Payment! This game is added to your library!\n";
//        wallet -= priceGame;
//        cout << "- Transaction Amount: -" << priceGame << " $\n";
//        cout << "- Current Balance: " << wallet << " $\n\n";
//    } else {
//        cout << "   "
//    }
    // Co the tbao thanh cong hay khong se thong bao trong purchaseGame --> nen chi viec return 0 hoac 1 thoi
    return wallet >= priceGame;
}

void User::addToCart(const Game &chosenGame) {
    // Kiem tra game da co trong lib truoc
//    if(isInLib(chosenGame.name) != -1) {
//        cout << "  Notification: Game " << chosenGame.name << " is already on your library!\n";
//        return;
//    }

    // Kiem tra da them game vao truoc do chua
    if(isInCart(chosenGame.name)  != -1) { // chi can kiem tra ten game la duoc roi
        cout << "  Notification: Game " << chosenGame.name << " is already on your cart!\n"; /* Dang lam ngang day 10:32 9/12 truoc khi di day*/
        return;
    }

    cout << "  Notification: Successfully adding game to cart!\n";
    cart.push_back(chosenGame);
}

bool User::isInCart(const string &nameGame) const {
    int id_cart = 0;
    for(Game g : cart) {
        if(g.name == nameGame) return id_cart; // Neu nam trong thi return chi so trong cart --> Tien trong viec xoa game from Cart (ham ben duoi)
        id_cart++;
    }
    return -1; // not found
}

void User::removeCart(const Game &removeGame) {
    int idRemove = isInCart(removeGame.name);
    if(idRemove != -1) { // Neu tim thay ten game trong cart
        cart.erase(cart.begin() + idRemove);
        cout << "  Notification: Successfully erasing game from cart!\n"; // can thay game bang ten cho all notification
    } else {
        cout << "  Notification: Failed erase game because it don't exist in cart!\n";
    }
}

void User::clearCart() {
    cout << "  Warning: This activity will erase all game of your cart!\n";
    cout << "  If you still want to erase, type Y or type N to stop: [Y/N] ";
    char choice; cin >> choice;
    if(choice == 'Y') cart.clear();
     else {
        cout << "  Notification: Stop erase data successfully!\n";
     }
}

void User::printCart() const { // Nen print theo dang bang o vuong --> Se update sau nay
    for(Game g : cart) {
        cout << "  === Game Specs ===\n";
        cout << "ID: " << g.id << '\n';
        cout << "Name: " << g.name << '\n';
        cout << "Price (after discount): " << g.afterDiscount << '\n';
        cout << "Genre: " << g.genre << '\n';
        cout << "Age Rating: " << g.ageRating << '\n';
        //cout << "Publisher: " << g.publisher << '\n'; // con check hoi y kien tu Dieu
        cout << '\n';
    }
}

void User::addToLib(const Game &chosenGame) { // add when complete purchasing game (khi mua game se check co game trong lib truoc chua --> nen k can check lai
    lib.push_back(chosenGame);
    cout << "  Notification: Install game " << chosenGame.name << " successfully\n";
}

bool User::isInLib(const string &nameGame) const {
    int id_lib = 0;
    for(Game g : lib) {
        if(g.name == nameGame) return id_lib;
        id_lib++;
    }
    return -1;
}

void User::uninstallGame(const Game &chosenGame) {
    int idUninstall = isInLib(chosenGame.name);
    if(idUninstall != -1) {
        lib.erase(lib.begin() + idUninstall);
        cout << "  Notification: Uninstall game " << chosenGame.name << " from library successfully!\n";
    } else {
        cout << "  Notification: Failed uninstall game because it dont't exist in library!\n";
    }
}

void User::printLib() const {
    cout << "  === Game library's " << name << " ===\n";
    for(Game g : lib) {
        cout << "  === Game Specs ===\n";
        cout << "ID: " << g.id << '\n';
        cout << "Name: " << g.name << '\n';
        //cout << "Price (after discount): " << g.afterDiscount << '\n'; da mua game roi thi khong can show gia nua
        cout << "Genre: " << g.genre << '\n';
        cout << "Age Rating: " << g.ageRating << '\n';
        //cout << "Publisher: " << g.publisher << '\n'; // con check hoi y kien tu Dieu
        cout << '\n';
    }
}




