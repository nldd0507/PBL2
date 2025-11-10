/*#ifndef USERS_H
#define USERS_H

#include <iostream>
#include "game.h"
using namespace std;

class User {
    string username;
    string name;
    string password;
    int age;
    double wallet; // bank account
    vector<Game> cart; // kieu du lieu la Game ==> con sau muon them Game thi truy cap toi games (thuoc GameManager roi push_back(games[id])
    vector<Game> lib; // cac game da mua ==> Tuong tu nhu cart
public:

    User() = default;
    User(const std::string& username, const std::string& password,
         const std::string& name, int age, double wallet)
        : username(username), password(password), name(name),
          age(age), wallet(wallet) {}

    // Info user
    friend istream &operator >>(istream &in, User &user);
    friend ostream &operator <<(ostream &out, const User &user);
    void getInfo(); // Nhap thong tin user
    void printInfo() const; // In ra all private

    // Wallet
    void addMoney(double amount);
    bool enoughMoney(const double &priceGame) const; // tham so priceGame lay tu games[id].afterDiscount
    // bool hay void: neu co thong bao nua

    // Cart
    //bool purchaseGame(const Game &idGame, const GameManager &gameManager); update after (MOST IMPORTANT FEATURE)
    void addToCart(const Game &chosenGame);
    void removeCart(const Game &removeGame); // xoa game theo ten or id ?
    void clearCart(); // khong duoc de const vi const thi khong the clear cart
    void printCart() const;
    int isInCart(const string &nameGame) const;

    // Library
    void addToLib(const Game &chosenGame);
    void uninstallGame(const Game &chosenGame);
    int isInLib(const string &nameGame) const; // mean: game da duoc mua va tai ve
    void printLib() const;

    // Con cac tinh nang da len y tuong (se lam neu co the): mua all game from cart, kiem tra & phan loai game voi do tuoi user
    /* Luu y: nhung y nghia cua cac ky hieu sau
    1. Cac ham trong class ma khong co truyen tham so <=> truy cap cac phan tu nam trong private
      VD: clearCart(), printCart(), printLib() thi tuc chung se truy cap vector<Game> Cart va vector<Game> Lib nen khong can truyen tham so

    2. Nhung ham bool Kiem tra(), void Print(), hay clear(): const nam o cuoi hang khai bao ham

    static std::vector<User*> allUsers;

    // quan ly file users.txt tong hop
    static void addUser(User* u); // add to allUsers
    static void loadAllUsersSummary(const std::string& file = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\users\\users.txt");
    static void saveAllUsersSummary(const std::string& file = "D:\\C++\\University\\Second Year\\Semester 3\\PBL2\\PBL2\\PBL2_Project\\data\\users\\users.txt");
    static void printAllUsers();

    // Rieng cho tung user.txt: U1.txt, U2.txt
    static void saveUserData(const User& user);
    static void loadUserDetailFromFile(User* u, const std::string& folderPath = "D:\\\\C++\\\\University\\\\Second Year\\\\Semester 3\\\\PBL2\\\\PBL2\\\\PBL2_Project\\\\data\\\\users\\\\");
    static User* checkUserExist(const std::string& username, const std::string& password);
    static User* registerUser(); // (not used now, kept for future)
    static void clearAllUsers();

     bool confirmPassword(const std::string& inputPrompt = "Enter your password to confirm: ");
     bool buyGameFromCart(const std::string& gameId);
};

#endif // USERS_H */

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include "game.h"

class User {
private:
    static std::vector<User*> allUsers;

    std::string username;
    std::string password;
    std::string name;
    int age;
    double wallet;

    std::vector<Game> cart; // gio hang game muon mua
    std::vector<Game> lib;  // game da so huu

    std::vector<std::string> cartIds;
    std::vector<std::string> libIds;

public:

    User() = default;
    User(const std::string& username, const std::string& password,
         const std::string& name, int age, double wallet)
        : username(username), password(password), name(name),
          age(age), wallet(wallet) {}

    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    double getWallet() const { return wallet; }

    const std::vector<Game>& getCart() const { return cart; }
    const std::vector<Game>& getLibrary() const { return lib; }

    void getInfo();
    void printInfo() const; // in ra all private
    void addMoney(double amount);
    bool enoughMoney(const double &priceGame) const;
    void addToCart(const Game &chosenGame);
    int isInCart(const std::string &nameGame) const;
    void removeCart(const Game &removeGame);
    void clearCart(); // khong the duoc de const vi khong the clear cart
    void printCart() const;
    void addToLib(const Game &chosenGame);
    int isInLib(const std::string &nameGame) const; // mean: game da duoc mua va tai ve
    void uninstallGame(const Game &chosenGame);
    void printLib() const;

    static void loadAllUsersSummary(); // doc info vao users.txt
    static void saveAllUsersSummary(); // ghi info vao users.txt
    void loadUserDetailFromFile();     // doc info rieng tung user
    void saveUserDetail() const;         // ghi info rieng tung user

    static User* checkUserExist(const std::string& username, const std::string& password);
    static std::vector<User*>& getAllUsers() { return allUsers; }
    bool confirmPassword();

    friend std::istream &operator>>(std::istream &in, User &user);
    friend std::ostream &operator<<(std::ostream &out, const User &user);
};

#endif // USER_H

