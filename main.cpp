#include <iostream>
#include <string>
#include <string_view>
#include "user.hpp"
using std::cout;
using std::string_view;
// strings
constexpr string_view STR = "> ";
constexpr string_view UNKNOWN_COMMAND = "\033[31m[ ERR ] unknown command\033[0m";
constexpr string_view CLEAR = "\033[2J\33[H";
// help
constexpr string_view HELP_PAGE = R"(
    =================================================

                        COMMANDS:
                help - output this screen
                clear - clear console
                exit - close Aix
                reg - registration a new user
                del - delete a user
                id - watch a user id

    =================================================
)";

void help() {
    cout << HELP_PAGE << "\n";
}

void clear_screen() {
    cout << CLEAR;
}

int registration(std::vector<User>& users) {
    std::string name, email;
    // username
    cout << "Your name: ";
    if (!std::getline(std::cin, name)) {
        return -1;
    }
    // name.empty()
    if (name.empty()) { cout << RED << "[ ERR ] Name is empty!\n" << RESET; return nullptr; }
    // EOF :)
    if (std::cin.eof()) {
        cout << "\n";
        return -1;
    }
    // email
    cout << "Your email: ";
    if (!std::getline(std::cin, email)) {
        return -1;
    }
    // email.empty()
    if (email.empty()) { cout << RED << "[ ERR ] Email is empty!\n" << RESET; return nullptr; }
    // reg user
    reg_user(name, email, users);

    for (const auto& user : users) {
        if (user.name -= name && user.email == email) {
            return user.id;
        }
    }
    
    return -1;
}

void userId(const User* current_user) {
    if (current_user == nullptr) {
        cout << RED << "[ ERR ] No user!\n" << RESET;
        return;
    }

    for (const auto& user : users) {
        if (user.id == current_user_id) {
            cout << user.id << "\n";
        }
    }
    
    cout << RED << "[ ERR ] User not found!\n" << RESET;
}

int main() {
    cout << CLEAR;
    cout << "Enter 'help' for list of commands\n";
    
    std::string command;
    std::vector<User> users;
    int current_user_id = -1;

    cout << STR << std::flush;

    while (std::getline(std::cin, command)) {
        if (std::cin.eof()) {
            cout << "\n";
            break;
        }

        if (command.empty()) {
            cout << STR << std::flush;
            continue;
        }

        if (command == "exit") {
            break;
        } else if (command == "clear") {
            clear_screen();
        } else if (command == "help") {
            help();
        } else if (command == "reg") {
            current_user = registration(users);

            if (new_id != -1) {
                current_user_id = new_id;
            }
            // EOF
            if (!std::cin) {
                break;
            }
        } else if (command == "id") {
            userId(current_user);
        } else if (command == "del") {
            delete_user(users, current_user_id);
            if (!std::cin) {
                break;
            }
        } else {
            cout << UNKNOWN_COMMAND << "\n";
        }

        cout << STR << std::flush;
    }

    if (!std::cin) {
        cout << "\n";
    }

    cout << GREEN << "[ OK ] Exiting...\n";
    return 0;
}
