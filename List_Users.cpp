#include "List_Users.h"
#include "Id_Counter_Manager.h"
#include "MyString.h"
#include <iostream>

const MyString List_Users::Name() const
{
    return "list-users";
}
bool List_Users::need_login() const
{
    return true;
}
bool List_Users::need_admin() const
{
    return true;
}
void List_Users::execute(std::stringstream& args, User*& user, Cinema& cinema,
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
Command* List_Users::clone() const
{
    return new List_Users();
}
