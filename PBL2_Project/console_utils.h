#ifndef Console_Utils_H
#define Console_Utils_H

#include <string>

#include <windows.h>
#include <iomanip>
#include <iostream>

namespace c_utils {
	inline void p_center(const std::string& title, int intro_width) {
		int title_padding = (intro_width - title.length()) / 2;
		std::cout << "*" << std::string(title_padding - 1, ' ');
		std::cout << title;
		std::cout << std::string(intro_width - 1 - title_padding - title.length(), ' ') << "*" << std::endl;
	}

    inline void p_task_menu(const std::string& title, const std::string task[], int n, int width) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        int title_padding = (width - title.length()) / 2;

        std::cout << std::string(width, '*') << std::endl;

        std::cout << "*" << std::string(title_padding, ' ');
        SetConsoleTextAttribute(hConsole, 11); // Blue
        std::cout << title;
        SetConsoleTextAttribute(hConsole, 7);  // White
        std::cout << std::string(width - 2 - title_padding - title.length(), ' ') << "*" << std::endl;
        std::cout << std::string(width, '*') << std::endl;

        for (int i = 0; i < n; i++) {
            std::cout << "* "
                << std::left << task[i]
                << std::string(width - 3 - task[i].length(), ' ')
                << "*" << std::endl;
        }

        std::cout << std::string(width, '*') << std::endl;
    }

    //sau nay co user thi dung
    //inline void p_task_menu(const std::string& title, const std::string task[], int n, int width, const std::string& usr, HANDLE hConsole) {
    //    int title_padding = (width - title.length()) / 2;

    //    std::cout << std::string(width, '*') << std::endl;
    //    std::cout << "*" << std::string(title_padding - 1, ' ');
    //    SetConsoleTextAttribute(hConsole, 11); // Blue
    //    std::cout << title;
    //    SetConsoleTextAttribute(hConsole, 7);  // White
    //    std::cout << std::string(width - 2 - title_padding - title.length() - usr.length(), ' ') << usr << " *" << std::endl;
    //    std::cout << std::string(width, '*') << std::endl;

    //    for (int i = 0; i < n; i++) {
    //        std::cout << "* "
    //            << std::left << task[i]
    //            << std::string(width - 3 - task[i].length(), ' ')
    //            << "*" << std::endl;
    //    }

    //    std::cout << std::string(width, '*') << std::endl;
    //}

}

#endif