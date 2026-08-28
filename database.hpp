#pragma once
#include <sqlite3.h>
#include <iostream>
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
    int db_regUser(const std::string& name, const std::string& email, const std::string& passw);
    bool db_delUser(int id);
    int db_sendMsg(int recipient_id, int author_id, const std::string& msg_text);
};
