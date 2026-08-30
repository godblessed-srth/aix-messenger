#pragma once
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <cstdint>
// database
class Database {
private:
    sqlite3* db = nullptr;
public:
    Database(const std::string& db_name);
    ~Database();
    // create tables
    bool initTables();
    //work with users & messages
    int64_t db_regUser(const std::string& name, const std::string& email, const std::string& passw);
    int64_t db_loginUser(const std::string& email, const std::string& passw);
    bool db_delUser(int64_t id);
    int64_t db_sendMsg(int64_t recipient_id, int64_t author_id, const std::string& msg_text);
};
