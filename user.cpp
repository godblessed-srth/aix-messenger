#include "user.hpp"
#include <iostream>
#include <functional>
// globals
extern std::vector<User> g_users;
extern int g_current_user_id = -1;
// hash email
std::string hashEmail(const std::string& email) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(email));
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
int reg_user(const std::string& name, const std::string& email) {
    if (name.empty() || email.empty()) {
        std::cout << RED << "[ ERR ] Name and email cannot be empty!\n" << RESET;
        return -1;
    }

    if (!ValidEmail(email)) {
        std::cout << RED << "[ ERR ] Invalid email format! Must contain '@' and '.'\n" << RESET;
        return -1;
    }

    std::string new_hash = hashEmail(email);
    
    for (const auto& user : users) {
        if (g_user.getHash() == new_hash) {
            std::cout << RED << "[ ERR ] Email " << email << "id already taken!\n" << RESET;
            return -1;
        }
    }

    int next_id = users.empty() ? 0 : g_users.back().getId() + 1;
    User new_user(name, email, next_id);
    g_users.push_back(new_user);
    
    std::cout << GREEN << "[ OK ] Successfully registred! Welcome!\n" << RESET;
    return next_id;
}
// delete user
void delete_user() {
    if (g_current_user_id == -1) {
        std::cout << RED << "[ ERR ] No user to delete!\n" << RESET;
        return;
    }
    
    int id_to_delete = g_current_user_id;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == id_to_delete) {
            g_users.erase(it);
            std::cout << GREEN << "[ OK ] User deleted: " << id_to_delete << RESET << "\n";
            g_current_user_id = -1;
            return;
        }
    }
    
    std::cout << RED << "[ ERR ] User not found!\n" << RESET;
}
