#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#inclide <fstream>
#include <sstream>
#include <unordered_map>
// colors
constexpr std::string_view RESET = "\033[0m";
constexpr std::string_view RED = "\033[31m";
constexpr std::string_view GREEN = "\033[32m";
// hash email
std::string hashEmail(const std::string& email);
// user
class User {
private:
    std::string name = "Guest";
    std::string email = "example@mail.com";
    std::string hash_em = "";
    int id = -1;  //unknown id
public:
    User() = default;
    User(const std::string& n, const std::string& e, int new_id) : name(n), email(e), id(new_id) {
        hash_em = hashEmail(e);
    }
    // getters
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getHash() const { return hash_em; }
    int getId() const { return id; }
    // setters
    void setName(const std::string& n) { name = n; }
    void setEmail(const std::string& e) {
        email = e;
        hash_em = hashEmail(e);
    }
    void setHash(const std::string& h) { hash_em = h; }
    void setId(int new_id) { id = new_id; }
};
// reg user
int reg_user(const std::string& name, const std::string& email, std::unordered_map<int, User>& users);
// delete user
void delete_user(std::unordered_map<int, User>& users, int& current_user_id);
