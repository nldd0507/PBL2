#ifndef USERS_H
#define USERS_H

#include <iostream>
#include "game.h"
using namespace std;

class User {
    int id; // id user
    string name;
    int age;
    double wallet; // bank account
    vector<Game> cart; // kieu du lieu la Game ==> con sau muon them Game thi truy cap toi games (thuoc GameManager roi push_back(games[id])
    vector<Game> lib; // cac game da mua ==> Tuong tu nhu cart
public:

    User() = default;
    User(int id, const string &name, int age, double wallet);
    ~User() = default;

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
    */
};

#endif // USERS_H
