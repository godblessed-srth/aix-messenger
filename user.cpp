#include "user.hpp"
#include <iostream>
#include <functional>
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
void reg_user(const std::string& name, const std::string& email, std::vector<User>& users) {
    int next_id = 0;

    if (!users.empty()) {
        next_id = users.back().getId() + 1;
    }
    
    if (name.empty() || email.empty()) {
        std::cout << RED << "[ ERR ] Name and email cannot be empty!\n" << RESET;
        return;
    }

    if (!ValidEmail(email)) {
        std::cout << RED << "[ ERR ] Invalid email format! Must contain '@' and '.'\n" << RESET;
        return;
    }

    std::string new_hash = hashEmail(email);
    
    for (const auto& user : users) {
        if (user.getHash() == new_hash) {
            std::cout << RED << "[ ERR ] Email " << email << "id already taken!\n" << RESET;
            return;
        }
    }
    
    User user(name, email, next_id);
    users.push_back(user);
    std::cout << GREEN << "[ OK ] Successfully registred! Welcome!\n" << RESET;
}
// delete user
void delete_user(std::vector<User>& users, int& current_user_id) {
    if (current_user_id == -1) {
        std::cout << RED << "[ ERR ] No user to delete!\n" << RESET;
        return;
    }

    int id_to_delete = current_user_id;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == id_to_delete) {
            users.erase(it);
            std::cout << GREEN << "[ OK ] User deleted: " << id_to_delete << RESET << "\n";
            current_user_id = -1;
            return;
        }
    }

    std::cout << RED << "[ ERR ] User not found!\n" << RESET;
}
