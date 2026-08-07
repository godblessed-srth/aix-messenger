#pragma once
#include <ctime>
#include <string>
#include <vector>

struct Message {
  int msg_id = -1;
  int author_id = -1;
  int recipient_id = -1;
  std::string msg_text;
  std::string timestamp;

  Message() = default;
  
  Message(int author, int recipient, const std::string& msg) : author_id(author), recipient_id(recipient), msg_text(msg) {
    auto now = std::time(nullptr);
    char buff[20]
    std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    timestamp = buff;
  }
}

extern std::vector<Message> g_msgs;
extern int g_msg_current_id = -1;
