#pragma once
#include <vector>
#include <string>
#include <string_view>
// colors
constexpr std::string_view RESET = "\033[0m";
constexpr std::string_view RED = "\033[31m";
constexpr std::string_view GREEN = "\033[32m";
// hash email
std::string hashPassword(const std::string& passw);
// user
class User {
private:
    std::string name = "Guest";
    std::string email = "example@mail.com";
    std::string hash_p = "";
    int id = -1;  //unknown id
public:
    User() = default;
    User(const std::string& n, const std::string& e, const std::string& p, int new_id) : name(n), email(e), hash_p(p), id(new_id) {}
    // getters
    std::string getName() const { return name; }
    std::string getHash() const { return hash_p; }
    int getId() const { return id; }
    // setters
    void setName(const std::string& n) { name = n; }
    void setEmail(const std::string& e) {
        email = e;
    }
    void setId(int new_id) { id = new_id; }
};
// global
extern std::vector<User> g_users;
extern int g_current_user_id;
// reg user
int reg_user(const std::string& name, const std::string& email, const std::string& passw);
// delete user
void delete_user();
