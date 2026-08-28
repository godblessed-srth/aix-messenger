#include "database.hpp"
#include <iostream>

Database::Database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "[ ERR ] Cannot open DB: " << sqlite3_errmsg(db) << std::endl;
    } else {
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::initTables() {
    // create users
    const char* createUsers =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
        "name TEXT UNIQUE NOT NULL, "
        "email TEXT UNIQUE NOT NULL, "
        "passw TEXT);";
    // create messages
    const char* createMsgs =
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "recipient_id INTEGER NOT NULL, "
        "author_id INTEGER NOT NULL, "
        "msg_text TEXT NOT NULL, "
        "FOREIGN KEY(author_id) REFERENCES users(id) ON DELETE CASCADE, "
        "FOREIGN KEY(recipient_id) REFERENCES users(id) ON DELETE CASCADE);";
    // error messahe
    char* errMsg = nullptr;
     // users
    if (sqlite3_exec(db, createUsers, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }
    // messages
    if (sqlite3_exec(db, createMsgs, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
// registration users
int Database::db_regUser(const std::string& name, const std::string& email, const std::string& passw) {
    const char* sql = "INSERT INTO users (name, email, passw) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, passw.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc == SQLITE_DONE) {
        return static_cast<int>(sqlite3_last_insert_rowid(db));
    }
    return -1;
}

int Database::db_sendMsg(int recipient_id, int author_id, const std::string& msg_text) {
    const char* sql = "INSERT INTO messages (recipient_id, author_id, msg_text) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_int(stmt, 1, recipient_id);
    sqlite3_bind_int(stmt, 2, author_id);
    sqlite3_bind_text(stmt, 3, msg_text.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc == SQLITE_DONE) {
        return static_cast<int>(sqlite3_last_insert_rowid(db));
    }

    return -1;
}

bool Database::db_delUser(int id) {
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc == SQLITE_DONE && sqlite3_changes(db) > 0) {
        return true;
    }

    return false;
}
