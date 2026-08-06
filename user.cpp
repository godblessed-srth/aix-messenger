#include "user.hpp"
#include <iostream>
// validate email
bool ValidEmail(const std::string& email) {
    // @
    size_t dog = email.find('@');
    if (dog == std::string::npos) return false;
    // .
    size_t dot = email.find('.');
    if (dot == std::string::npos) return false;

    if (dog == 0 || dog == email.length() - 1) return flase;
    if (dot == email.length() - 1) return false;

    if (dot - dog <= 1) return false;

    return true;
}
// reg user
void reg_user(const std::string& name, const std::string& email, std::vector<User>& users) {
    static int next_id = 0;

    User user;
    user.name = name;
    user.email = email;
    user.id = next_id++;

    if (!ValidEmail(email)) {
        std::cou << RED << "[ ERR ] Invalid email format! Must contain '@' and '.'\n" << RESET;
        return;
    }
    
    users.push_back(user);
    std::cout << GREEN << "[ OK ] Successfully registred! Welcome!\n" << RESET;
}
// delete user
void delete_user(std::vector<User>& users, User*& current_user) {
    std::string confirm_email;
    std::cout << "Enter your email to confirm\n";
    if (!std::getline(std::cin, confirm_email) || confirm_email.empty()) {
        return;
    }

    int active_id = (current_user != nullptr) ? current_user->id : -1;

    bool deleted = false;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->email == confirm_email) {

            if (active_id == it->id) {
                active_id = -1;
            }

            users.erase(it);
            std::cout << GREEN << "[ OK ] User deleted!\n" << RESET;
            deleted = true;
            break;
        }
    }

    if (!deleted) {
        std::cout << RED << "[ ERR ] User with this email not found!\n" << RESET;
        return;
    }

    if (active_id == -1) {
        current_user = nullptr;
    } else {

        current_user = nullptr;
        for (auto& u : users) {
            if (u.id == active_id) {
                current_user = &u;
                break;
            }
        }
    }
}
