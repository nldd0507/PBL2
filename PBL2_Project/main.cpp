#include <iostream>
#include "publisher.h"
#include "user.h"
#include "menu.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
 // console width
void admin_Login_Screen() {
    cout << "This is admin screen" << endl;
}
void user_Login_Screen() {
    cout << "This is user screen" << endl;
}
void publisher_Login_Screen() {
    cout << "This is publisher screen" << endl;
}
int main() {
    ///* Dieu 05/10/2025 */          
    Menu menu;
    menu.handleMainMenu();
    ///* --------------  */


    // B1. Đọc danh sách publisher
    /*Publisher::importFromFile();
    Publisher* pub = Publisher::getPublisherByName("Square Enix");
    delete pub;
    Game::importFromFile();
    Game::exportToFile();*/
    return 0;
}
///////ID ; Name ; Price ;  Discount;  Genre ; AgeRating ;  Pub Sort Name
