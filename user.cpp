#include "user.hpp"
#include "database.hpp"
#include <iostream>
#include <functional>
// globals
extern Database db;
std::vector<User> g_users;
int g_current_user_id = -1;
// hash email
std::string hashPassword(const std::string& passw) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(passw));
}
// validate email
bool ValidEmail(const std::string& email) {
    // @
    size_t dog = email.find('@');
    if (dog == std::string::npos) return false;
    // .
    size_t dot = email.find('.');
    if (dot == std::string::npos) return false;

    if (dog == 0 || dog == email.length() - 1) return false;
    if (dot == email.length() - 1) return false;

    if (dot - dog <= 1) return false;

    return true;
}
// reg user
int reg_user(const std::string& name, const std::string& email, const std::string& passw) {
    if (name.empty() || email.empty()) {
        std::cout << RED << "[ ERR ] Name and email cannot be empty!\n" << RESET;
        return -1;
    }

    if (!ValidEmail(email)) {
        std::cout << RED << "[ ERR ] Invalid email format! Must contain '@' and '.'\n" << RESET;
        return -1;
    }

    std::string new_hash = hashPassword(passw);

    int next_id = db.db_regUser(name, email, new_hash);

    if (next_id == -1) {
        std::cout << RED << "[ ERR ] User is exists\n" << RESET;
        return -1;
    }

    User new_user(name, email, new_hash, next_id);
    g_users.push_back(new_user);

    std::cout << GREEN << "[ OK ] Successfully registered! Welcome!\n" << RESET;
    return next_id;
}
// delete user
void delete_user() {
    if (g_current_user_id == -1) {
        std::cout << RED << "[ ERR ] No user to delete!\n" << RESET;
        return;
    }

    if (db.db_delUser(g_current_user_id)) {
        std::cout << GREEN << "[ OK ] User deleted: " << g_current_user_id << RESET << "\n";

        for (auto it = g_users.begin(); it != g_users.end(); ++it) {
            if (it->getId() == g_current_user_id) {
                g_users.erase(it);
                break;
            }
        }

        g_current_user_id = -1;
    } else {
        std::cout << RED << "[ ERR ] User not found!\n" << RESET;
    }
}
