#include <iostream>
#include <algorithm>
#include <vector>
#include "message.hpp"
#include "user.hpp"

int g_current_msg_id = -1;
std::vector<Message> g_msgs;

int send_msg(int author_id, int recipient_id, const std::string& msg_text) {
  bool author = false, recipient = false;
  std::string recipient_name;

  for (const auto& user : g_users) {
    if (user.getId() == author_id) {
      author = true;
      break;
    }
  }
  if (!author) {
     return -1;
  }

  for (const auto& user : g_users) {
    if (user.getId() == recipient_id) {
      recipient = true;
      recipient_name = user.getName();
      break;
    }
  }
  if (!recipient) {
    std::cout << RED << "[ ERR ] REcipient " << recipient_id << " not found!\n" << RESET;
    return -1;
  }

  if (msg_text.empty()) {
    std::cout << RED << "[ ERR ] Cannot send empty message!\n" << RESET;
  }
}
