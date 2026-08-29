#include <iostream>
#include <algorithm>
#include <vector>
#include "message.hpp"
#include "user.hpp"
int send_msg(Database& db, int recipient_id, int author_id, const std::string& msg_text) {
  if (msg_text.empty()) {
    std::cout << RED << "[ ERR ] Cannot send empty message!\n" << RESET;
    return -1;
  }

  int next_id = db.db_sendMsg(recipient_id, author_id, msg_text);
  
  if (next_id == -1) {
    std::cout << RED << "[ ERR ] Recipient or Author ID not found\n" << RESET;
    return -1;
  }

  return next_id;
}
