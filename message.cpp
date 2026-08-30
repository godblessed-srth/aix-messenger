#include <iostream>
#include <algorithm>
#include "message.hpp"
#include "user.hpp"
int64_t send_msg(Database& db, int64_t recipient_id, int64_t author_id, const std::string& msg_text) {
  if (msg_text.empty()) {
    std::cout << RED << "[ ERR ] Cannot send empty message!\n" << RESET;
    return -1;
  }

  int64_t next_id = db.db_sendMsg(recipient_id, author_id, msg_text);
  
  if (next_id == -1) {
    std::cout << RED << "[ ERR ] Recipient or Author ID not found\n" << RESET;
    return -1;
  }

  return next_id;
}
