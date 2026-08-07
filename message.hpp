#pragma once
#include <ctime>
#include <string>
#include <vector>
// struct
struct Message {
  int msg_id = -1;
  int author_id = -1;
  int recipient_id = -1;
  std::string msg_text;
  std::string timestamp;

  Message() = default;
    
  Message(int author, int recipient, const std::string& msg, int new_id) : author_id(author), recipient_id(recipient), msg_text(msg), msg_id(new_id) {
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
// global
extern std::vector<Message> g_msgs;
extern int g_msg_current_id;

int send_msg(int recipient_id, int author_id, const std::string& msg_text); 
