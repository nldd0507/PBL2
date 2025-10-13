#ifndef MENU_H
#define MENU_H

#include "publisher.h"
#include <string>
class Menu {
public:
	void handleMainMenu();
private: 
	bool adminLogin() { return 1; };
	void handleAdminMenu() {};

	bool userLogin() { return 1; }
	void handleUserMenu() {};

	Publisher* publisherLogin();
	void handlePublisherMenu(Publisher *publisher);
};

#endif
