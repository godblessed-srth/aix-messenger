#include "user.hpp"
#include "database.hpp"
#include <crypt.h>
#include <stdexcept>
#include <iostream>
#include <functional>
// hash email
std::string hashPassword(const std::string& passw) {
    char salt[CRYPT_GENSALT_OUTPUT_SIZE];

    crypt_data data;

    if (!crypt_gensalt_rn("$y$", 10, nullptr, 0, salt, sizeof(salt))) {
        return "";
    }

    char* hashed = crypt_rn(passw.c_str(), salt, &data, sizeof(data));

    if (!hashed) {
        return "";
    }

    return std::string(hashed);
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
int reg_user(Database& db, const std::string& name, const std::string& email, const std::string& passw) {
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

    std::cout << GREEN << "[ OK ] Successfully registered! Welcome!\n" << RESET;
    return next_id;
}
// delete user
void delete_user(Database& db, int& current_user_id) {
    if (current_user_id == -1) {
        std::cout << RED << "[ ERR ] No user to delete!\n" << RESET;
        return;
    }

    if (db.db_delUser(current_user_id)) {
        std::cout << GREEN << "[ OK ] User deleted: " << current_user_id << RESET << "\n";

        current_user_id = -1;
    } else {
        std::cout << RED << "[ ERR ] User not found!\n" << RESET;
    }
}
