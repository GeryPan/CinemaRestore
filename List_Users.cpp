#include "List_Users.h"
#include <iostream>

const char* Name()
{
    return "list-users";
}
bool need_login()
{
    return true;
}
bool need_admin()
{
    return true;
}
void execute(std::stringstream& args, User*& user, Cinema& cinema,
    Vector<User*>& users, Id_Counter_Manager& id_manager)
{
    if (users.Size() == 0) {
        throw std::runtime_error("No users found.");
    }
    std::cout << "Registered users:\n";
    for (unsigned i = 0; i < users.Size(); i++)
    {
        std::cout << "- " << users[i]->Username();
         if (users[i]->is_admin())
            std::cout << " ADMIN";
        std::cout << "\n";
    }
}
}