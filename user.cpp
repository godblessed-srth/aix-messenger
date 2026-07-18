#include "user.hpp"
#include <iostream>
// reg user
void reg_user(const std::string& name, const std::string& email, std::vector<User>& users) {
    static int next_id = 0;

    User user;
    user.name = name;
    user.email = email;
    user.id = next_id++;

    users.push_back(user);

    std::cout << GREEN << "[ OK ] Successfully registred! Welcome!\n" << RESET;
}
// delete user
void delete_user(std::vector<User>& users, User*& current_user) {
    std::string confirm_email;
    std::cout << "Enter your email to confirm\n"; // Твой стиль вывода

    if (!std::getline(std::cin, confirm_email) || confirm_email.empty()) {
        return;
    }

    // 1. Запоминаем ID того, кто СЕЙЧАС залогинен (если кто-то залогинен)
    int active_id = (current_user != nullptr) ? current_user->id : -1;

    // 2. Ищем и удаляем аккаунт по введенной почте
    bool deleted = false;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->email == confirm_email) {

            // Если пользователь удаляет САМ СЕБЯ, сразу сбрасываем ID активного
            if (active_id == it->id) {
                active_id = -1;
            }

            users.erase(it); // Удаляем из вектора (память сдвигается!)
            std::cout << GREEN << "[ OK ] User deleted!\n" << RESET;
            deleted = true;
            break; // Выходим из цикла поиска, так как удаление завершено
        }
    }

    if (!deleted) {
        std::cout << RED << "[ ERR ] User with this email not found!\n" << RESET;
        return;
    }

    // 3. СПАСЕНИЕ СЕССИИ (Middle+ подход):
    // Если активный юзер удалил сам себя, просто зануляем указатель
    if (active_id == -1) {
        current_user = nullptr;
    } else {
        // Если был удален КТО-ТО ДРУГОЙ, адрес активного юзера в памяти СДВИГНУЛСЯ.
        // Мы обязаны найти его в обновленном векторе по ID и перезаписать указатель!
        current_user = nullptr; // Временно зануляем на случай сбоя
        for (auto& u : users) {
            if (u.id == active_id) {
                current_user = &u; // Нашли его на новом месте в памяти и привязали!
                break;
            }
        }
    }
}
