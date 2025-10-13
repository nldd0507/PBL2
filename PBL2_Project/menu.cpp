#include "menu.h"
#include "game.h"
#include "publisher.h"

#include "console_utils.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

const int c_width = 100;

const string MAIN_TASKS[] = {
    "1. User",
    "2. Publisher",
    "0. Exit"
};

Publisher* Menu::publisherLogin() {
    std::ifstream fin("data/publishers/publishers.txt");
    if (!fin.is_open()) {
        std::cerr << "Error: cannot open publisher file." << endl;
        return nullptr;
    }

    std::string username, password;
    c_utils::p_center("PUBLISHER LOGIN", c_width);
    std::cout << "Username (ID): ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    Publisher* p = Publisher::checkPublisherExist(username, password);
    if (p) {
        std::cout << "Login successful!" << endl;
        fin.close();
        return p;
    }

    fin.close();
    std::cout << "Login failed! Invalid ID or password." << endl;
    std::cout << "Press Enter to continue...";
    std::cin.get();
    return nullptr;
}

void Menu::handleMainMenu() {
    string choose;
    Publisher::loadAllPublishersSummary();
    Publisher::saveAllPublishersSummary();
    Game::loadAllGamesSummary(); 
    Game::saveAllGamesSummary();
    do {
        system("cls");
        c_utils::p_task_menu(" S T O R E ", MAIN_TASKS, 3, c_width);
        getline(cin, choose);
        if (choose == "/admin") {
            if (adminLogin()) {
                handleAdminMenu();
            }
        }
        else if (choose == "1") {
            if (userLogin()) {
                handleUserMenu();
            }
        }
        else if (choose == "2") {
            Publisher* pub = publisherLogin();
            if (pub) {
                handlePublisherMenu(pub);
            }
        }
        else if (choose == "0") {
            //cout << "Store is closing";
            utils::dotAnimation("Store is closing",2);
        }
        else {
            cout << "Input Error!" << endl;
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while (choose!="0");
}

const string PUBLISHER_TASKS[] = {
    "1. Show Owned Games",
    "2. Add New Game",
    "3. Edit Game",
    "4. Delete Game",
    "5. Change Password",
   // "6. Load From File",
    "0. Return"
};

void Menu::handlePublisherMenu(Publisher *publisher) {
    string choose;
    do {
        system("cls"); 
        c_utils::p_task_menu(" PUBLISHER MENU ", PUBLISHER_TASKS, 6, c_width);
        getline(cin, choose);

        if (choose == "1") {

            publisher->showAllGames();
            cin.get();
        }
        else if (choose == "2") {
            if (publisher->confirmPassword()) {
                publisher->addGame();
                cin.get();
            }
            else {
                utils::dotAnimation("Too many failed attempts. Logging out", 3, 200);
                break;
            }
        }
        else if (choose == "3") {
            if (publisher->confirmPassword()) {  
                publisher->editGame();
                cin.get();
            }
            else {
                utils::dotAnimation("Too many failed attempts. Logging out", 3, 200);
                break;
            }
        }
        else if (choose == "4") {
            if (publisher->confirmPassword()) {
                publisher->deleteGame();
                cin.get();
            }
            else {
                utils::dotAnimation("Too many failed attempts. Logging out", 3, 200);
                break;
            }
        }
        else if (choose == "5") {
            int c = publisher->changePassword();
            if (c==1 || c==2) {
                cin.get();
            }
            else if(c==0){
                utils::dotAnimation("Too many failed attempts. Logging out", 3, 200);
                break;
            }

        }
        else if (choose == "6") {
           // publisher->loadFromFile();
            cin.get();
        }
        else if (choose == "0") {
            
            utils::dotAnimation("Turning back", 3, 200);
            break;
        }
        else {
            cout << "Error.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    } while (choose != "0");
}
