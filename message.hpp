#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "database.hpp"
// struct
struct Message {
  int recipient_id = -1;
  int author_id = -1;
  std::string msg_text;
  int msg_id = -1;
  std::string timestamp;

  Message() = default;
    
  Message(int recipient, int author, const std::string& msg, int new_id) : recipient_id(recipient),author_id(author), msg_text(msg), msg_id(new_id) {
      auto now = std::time(nullptr);
      char buff[20];
      // localtime validate
      auto time_ptr = std::localtime(&now);
      if (time_ptr != nullptr) {
        std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", time_ptr);
        timestamp = buff;
      } else {
        timestamp = "1970-01-01 00:00:00";
    }
  }
};

int send_msg(Database& db, int recipient_id, int author_id, const std::string& msg_text);
