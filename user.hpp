#pragma once
#include <vector>
#include <string>
#include <string_view>
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
    std::string getHash() const { return hash_em; }
    int getId() const { return id; }
    // setters
    void setName(const std::string& n) { name = n; }
    void setEmail(const std::string& e) {
        email = e;
        hash_em = hashEmail(e);
    }
    void setId(int new_id) { id = new_id; }
};
// global
extern std::vector<User> g_users;
extern int g_current_user_id;
// reg user
int reg_user(const std::string& name, const std::string& email);
// delete user
void delete_user();
