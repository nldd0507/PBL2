#ifndef MENU_H
#define MENU_H

#include <string>
#include "publisher.h"
#include "user.h"

class Menu {
public:
    static void handleMainMenu();

private:
    static Publisher* publisherLogin();
    static void handlePublisherMenu(Publisher* publisher);

    // them vao
    static User* userLogin();
    static void handleUserMenu(User* user);

    static bool adminLogin();
    static void handleAdminMenu();
};

#endif
