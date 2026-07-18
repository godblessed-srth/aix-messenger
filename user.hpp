#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
// colors
constexpr std::string_view RESET = "\033[0m";
constexpr std::string_view RED = "\033[31m";
constexpr std::string_view GREEN = "\033[32m";
// user
struct User {
    std::string name = "Guest";
    std::string email = "example@mail.com";
    int id = -1;  //unknown id
};
// reg user
void reg_user(const std::string& name, const std::string& email, std::vector<User>& users);
// delete user
void delete_user(std::vector<User>& users, User*& current_user);
