#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include "user.hpp"
#include "message.hpp"
#include "database.hpp"
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
                send - send a message for any user

    =================================================
)";

void help() {
    cout << HELP_PAGE << "\n";
}

void clear_screen() {
    cout << CLEAR;
}

int registration(Database& db) {
    std::string name, email, passw;
    // username
    cout << "Your name: ";
    if (!std::getline(std::cin, name)) {
        return -1;
    }
    // name.empty()
    if (name.empty()) { cout << RED << "[ ERR ] Name is empty!\n" << RESET; return -1; }
    // EOF :)
    if (std::cin.eof() || !std::cin) {
        cout << "\n";
        return -1;
    }
    // email
    cout << "Your email: ";
    if (!std::getline(std::cin, email)) {
        return -1;
    }
    // email.empty()
    if (email.empty()) { cout << RED << "[ ERR ] Email is empty!\n" << RESET; return -1; }
    // password
    cout << "Enter password: ";
    if (!std::getline(std::cin, passw)) {
        return -1;
    }
    // email.empty()
    if (passw.empty()) { cout << RED << "[ ERR ] Password is empty!\n" << RESET; return -1; }
    // reg user
    return reg_user(db, name, email, passw);
}

int sendMsg(Database& db, int current_user_id) {
    std::string msg_text, recip_inp;
    int recip_id;
    
     if (std::cin.eof() || !std::cin) {
        cout << "\n";
        return -1;
    }
    
    if (current_user_id == -1) {
        cout << RED << "[ ERR ] User not registered!\n" << RESET;
        return -1;
    }
    
    cout << "Enter recipient ID: ";
    if (!std::getline(std::cin, recip_inp)) {
        return -1;
    }
    
    if (recip_inp.empty()) {
        cout << RED << "[ ERR ] ID is empty!\n" << RESET;
        return -1;
    }
    
    for (char c : recip_inp) {
        if (!std::isdigit(c)) {
            cout << RED << "[ ERR ] ID must be a number!\n" << RESET;
            return -1;
        }
    }
    
    recip_id = std::stoi(recip_inp);
    
    cout << "Enter message: \n";
    if (!std::getline(std::cin, msg_text)) {
        return -1;
    }
    
    if (msg_text.empty()) {
        cout << RED << "[ ERR ] Cannot send empty message!\n" << RESET;
        return -1;
    }
    
    int res = db.db_sendMsg(recip_id, current_user_id, msg_text);
    
    if (res != -1) {
        cout << GREEN << "[ OK ] Message sent!\n" << RESET;
    } else {
        cout << RED << "[ ERR ] Recipient or Author ID not found\n" << RESET;
        return -1;
    }

    return res;
}

int main() {
    Database db("aix.db");
    db.initTables();
    cout << CLEAR;
    cout << "Enter 'help' for list of commands\n";
    
    int current_user_id = -1;
    std::string command;

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
            int new_id = registration(db);

            if (new_id != -1) {
                current_user_id = new_id;
            }
        } else if (command == "id") {
            if (current_user_id == -1) {
                cout << RED << "[ ERR ] No user!\n" << RESET;
                cout << STR << std::flush;
                continue;
            }

            cout << current_user_id << "\n";
        } else if (command == "del") {
            delete_user(db, current_user_id);
            if (!std::cin) {
                break;
            }
        } else if (command == "send") {
            sendMsg(db, current_user_id);
        } else {
            cout << UNKNOWN_COMMAND << "\n";
        }

        cout << STR << std::flush;
    }

    if (!std::cin) {
        cout << "\n";
    }

    cout << GREEN << "[ OK ] Exiting...\n" << RESET;
    return 0;
}
